package Player
{	
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
	
	public class BirdManager
	{		
		//Objects
		var bird:Bird;
		var mainClass:MainManager;
		var stage:Stage
		var parentClip:MovieClip;
		
		//Move lerp
		var lerpSpeed:Number = 0.3;
		
		//Facing
		var previousX:Number = 0;
		var facingRight:Boolean = true;
		
		//Poop
		var poopIntervalCD:Number = 500;
		var poopIntervalCDRate:Number = 1;
		var startPoop:Boolean = false;
		
		var poopTimer:Timer = new Timer(20);
		var laxTimer:Timer = new Timer(100);
		
		public function BirdManager(argParentClip:MovieClip, main:MainManager)
		{
			//Ref
			mainClass = main;
			stage = main.stage;
			parentClip = argParentClip;
		}		
		
		//{Reveal/Hide		
		public function Reveal()
		{
			stage.addEventListener(MouseEvent.MOUSE_DOWN, StartPoopTimer);
			stage.addEventListener(MouseEvent.MOUSE_UP, StopPoopTimer);
			poopTimer.addEventListener(TimerEvent.TIMER, MakePoop);
			
			//Add bird
			bird = new Bird(parentClip, mainClass);
			
			MainManager.BirdLayer.addChild(bird);
			bird.setX(mainClass.stage.stageWidth / 2);			
			bird.setY(50);
			AudioManager.PlayPigeonSpawn();	
		}
		
		public function CleanUp ()
		{
			trace("BirdManager Cleanup");
			stage.removeEventListener(MouseEvent.MOUSE_DOWN, StartPoopTimer);
			stage.removeEventListener(MouseEvent.MOUSE_UP, StopPoopTimer);
			poopTimer.removeEventListener(TimerEvent.TIMER, MakePoop);
			bird.CleanUp();
		}
		//}
		
		public function SetStun(isTrue:Boolean)
		{
			bird.SetStun(isTrue);
		}
		
		public function MainLoop ()
		{
			MoveAndScale ();
		}
		
		//{Movement
		function MoveAndScale ():void
		{
			//Lerp
			var curX = bird.getX();
			var tgtX = curX + (stage.mouseX - curX)*lerpSpeed;
			
			//Move		
			bird.setX(tgtX);

			//Facing
			var xDiff : Number = stage.mouseX - previousX;
			if (!facingRight && xDiff > 0)
			{
				bird.FaceRight(true);
				facingRight = true;
			}
			else if (facingRight && xDiff < 0)
			{
				bird.FaceRight(false);
				facingRight = false;
			}
			previousX = stage.mouseX;
			
			//Update Bird
			bird.MainLoop();
		}
		//} 
		
		//{Poop
		function StartPoopTimer (event:MouseEvent) 
		{
			poopTimer.start();
			//Poo();
		}
		
		function StopPoopTimer (event:MouseEvent) 
		{
			poopTimer.stop();
			poopTimer.reset();
		}
		
		function MakePoop(event:TimerEvent)
		{		
			if (MainManager.SpendPoop())
			{
				bird.Poo();
				MainManager.DoScreenShake ();
			}
			else
			{
				//poopTimer.stop();
				//poopTimer.reset();
			}
		}
		//}
	}	
}