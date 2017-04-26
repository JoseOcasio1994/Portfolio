package Player
{
	import Player.Control.*;
	import UI.*;
	import Audio.*;
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.net.URLRequest;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.ui.Keyboard;
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	
	public class Bird extends Renderable
	{
		static var normalPoop:Array = new Array();
		static var flattenedPoops:Array = new Array();
		static var poopCrumbs:Array = new Array();
		
		public var inDiarrhea:Boolean = false;
		
		//Objects
		var mainClass:MainManager;
		var mainStage:Stage;
		
		//Poop
		var startPoop:Boolean = false;
		var maxLaxPoop:int = 4;
		var laxativePooped:int = 0;
		var laxRecoveryTimer:Timer = new Timer(200);
		var controlScheme:PlayerControlScheme;
		var muzzleFlash:MuzzleFlash;
		
		//Attributes
		var stunned:Boolean = false;
		
		//Stun
		//Stun
		var stunRecoveryTimer:Timer = new Timer(1000);
		
		public function GetPoops():Array  { return normalPoop; }
		
		public function GetStunned():Boolean  { return stunned; }
		
		public function SetStunned(value:Boolean):Boolean  { return stunned = value; }
		
		public function Bird(argParentClip:MovieClip, main:MainManager)
		{
			mainClass = main;
			mainStage = main.stage;
			
			super(argParentClip, "Assets/Player/imgPlayer.swf");
			muzzleFlash = new MuzzleFlash(MainManager.NPCLayer);
			muzzleFlash.setY(getY()+80);
			ResumeControl();
			Reveal();
		}
		
		public static function ReflectPoop(index:int)
		{
			for (var i:int = 0; i < 3; i++)
			{
				var crumb:PoopCrumbs = new PoopCrumbs();
				crumb.setX(normalPoop[index].getX());
				crumb.setY(normalPoop[index].getY());
				poopCrumbs.push(crumb);
			}
			
			normalPoop[index].SetSpeed(-20);
			normalPoop[index].Reflected = true;
			ScreenShake.DoShake(false);
		}
		
		public static function RemovePoop(index:int)
		{
			normalPoop[index].CleanUp();			
			normalPoop[index] = null;
			normalPoop.splice(index, 1);
		}
		
		//{Reveal/Hide		
		public function Reveal()
		{
			setX(mainStage.stageWidth / 2);
			setY(50);
			AttachToParent(true);
			
			laxRecoveryTimer.addEventListener(TimerEvent.TIMER, LaxativeHandler);
			stunRecoveryTimer.addEventListener(TimerEvent.TIMER, StunTimerUp);
			AudioManager.PlayPigeonSpawn();
		}
		
		public function PreCleanUp()
		{
			laxRecoveryTimer.stop();
			stunRecoveryTimer.stop();
			controlScheme.CleanUp();
		}
		
		public function CleanUp()
		{
			AttachToParent(false);
			
			laxRecoveryTimer.removeEventListener(TimerEvent.TIMER, LaxativeHandler);
			stunRecoveryTimer.removeEventListener(TimerEvent.TIMER, StunTimerUp);
			for (var i:int = normalPoop.length - 1; i >= 0; i--)
			{
				normalPoop[i].CleanUp();
				normalPoop[i] = null;
			}
			
			for (var j:int = flattenedPoops.length - 1; j >= 0; j--)
			{
				flattenedPoops[j].CleanUp();
				flattenedPoops[j] = null;
			}
			
			for (var k:int = poopCrumbs.length - 1; k >= 0; k--)
			{
				poopCrumbs[k].CleanUp();
				poopCrumbs[k] = null;
			}
			
			poopCrumbs = new Array();
			flattenedPoops = new Array();
			normalPoop = new Array();
		}//}
		
		//{Stun
		public function Stunned()
		{
			stunRecoveryTimer.start();
			stunned = true;
			controlScheme.StunStarted();
			if (!inDiarrhea)
			{
				assetClip.gotoAndPlay("Stun");
			}
		}
		
		function StunTimerUp(timerEvent:TimerEvent):void
		{
			assetClip.gotoAndPlay("Fly");
			controlScheme.StunFinished();
			stunRecoveryTimer.stop();
			stunRecoveryTimer.reset();
			stunned = false;
		}//}
		
		public function MainLoop()
		{
			if (loadCompleted)
			{
				controlScheme.MainLoop();
				if (!stunned && !inDiarrhea && !assetClip.isPlaying)
				{
					assetClip.gotoAndPlay("Fly");
				}				
			}
			
			//Update poop. 
			for (var i:int = normalPoop.length - 1; i >= 0; i--)
			{
				if (normalPoop[i].MainLoop())
				{					
					var flatten:PoopFlatten = new PoopFlatten(MainManager.NonNPCLayer);
					flatten.setX(normalPoop[i].getX());
					flatten.setY(normalPoop[i].getY() + (Math.random()*20) + 5);
					flattenedPoops.push(flatten);
					RemovePoop(i);
				}
			}
			
			for (var j:int = poopCrumbs.length - 1; j >= 0; j--)
			{
				poopCrumbs[j].MainLoop();
			}
		}
		
		public function Pause(isTrue:Boolean)
		{
			controlScheme.Pause(isTrue);
			if (assetClip != null)
			{
				if (isTrue)
				{
					assetClip.stop();
				}
				else
				{
					assetClip.play();
				}
			}
		}
		
		//{Laxative
		public function LaxativeActivated()
		{
			inDiarrhea = true;
			laxativePooped = 1;
			CanPoopCheck();
			laxRecoveryTimer.start();
			LaxativeLoseControl();
			assetClip.gotoAndPlay("Lax");
		}
		
		function LaxativeHandler(event:TimerEvent)
		{
			if (MainManager.SpendPoop())
			{
				CanPoopCheck();
			}
			laxativePooped++;
			if (laxativePooped == maxLaxPoop)
			{
				assetClip.gotoAndPlay("Fly");
				inDiarrhea = false;
				laxRecoveryTimer.stop()
				laxRecoveryTimer.reset()
				ResumeControl();
			}
		}//}
		
		//{Poop	
		public function CanPoopCheck()
		{
			if (MainManager.SpendPoop())
			{
				var poop:Poop = new Poop(MainManager.NonNPCLayer);
				normalPoop.push(poop);
				
				poop.setX(getClip().x);
				poop.setY(getClip().y);
				
				addChild(poop);
				
				muzzleFlash.getAssetClip().gotoAndPlay(1);
				muzzleFlash.setX(getX());
				AudioManager.PlayPoop();
				
				ScreenShake.DoShake(false);
			}
		}//}
		
		function ResumeControl()
		{
			if (controlScheme != null)
				controlScheme.CleanUp();
			
			if (MainManager.IsCtrlFreakOn())
			{
				controlScheme = new KeyboardControl(mainStage, this, CanPoopCheck);
			}
			else
			{
				controlScheme = new MouseControl(mainStage, this, CanPoopCheck);
			}
		}
		
		function LaxativeLoseControl()
		{
			if (controlScheme != null)
			{
				controlScheme.CleanUp();
			}
			controlScheme = new LaxativeControl(mainStage, this, CanPoopCheck);
		}
	}
}