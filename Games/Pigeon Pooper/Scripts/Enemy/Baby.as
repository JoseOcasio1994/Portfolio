package Enemy
{	
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	
	public class Baby extends EnemyBase
	{	
		var isCovered:Boolean;
		var mother:Mother;
		var coveredDuration:Timer;
		var exposedDuration:Timer;
		
		public function GetIsCovered():Boolean { return isCovered;}
		
		public function Baby(argParentClip:MovieClip, argMother:Mother)
		{
			super(argParentClip, "Assets/Art/imgBaby.swf");
			mother = argMother;
			
			speed = 5;
			points = 2000;
			
			coveredDuration = new Timer(2000);
			exposedDuration = new Timer(2000);
			exposedDuration.start();
			isCovered = false;
			SetStats(mainStage.stageHeight - 100);
		}
		
		protected override function LoadComplete() 
		{
			coveredDuration.addEventListener(TimerEvent.TIMER, CoveredHandler);
			exposedDuration.addEventListener(TimerEvent.TIMER, ExposedHandler);
		}
		
		public function modX():void  { baseClip.x += speed; }

		public function setParent(newParent:Mother):void  { mother = newParent; }
		
		public function getParent():MovieClip  { return mother; }
		
		public function setPoints(newPoints:Number):void  { points = newPoints; }
		
		public override function removeSelf():void
		{
			coveredDuration.removeEventListener(TimerEvent.TIMER, CoveredHandler);
			exposedDuration.removeEventListener(TimerEvent.TIMER, ExposedHandler);
			coveredDuration.stop();
			exposedDuration.stop();
			
			if (!cleanedUp)
			{
				cleanedUp = true;
				AttachToParent(false);						
			}

			if (mother != null)
			{
				mother.baby = null;
			}
		}
		
		private function ExposedHandler(e:TimerEvent):void
		{
			isCovered = false;
			exposedDuration.stop()				
			coveredDuration.start();
		}
		
		private function CoveredHandler(e:TimerEvent):void
		{
			isCovered = true;
			coveredDuration.stop()
			exposedDuration.start();
		}
		
		public override function MainLoop():void
		{			
			if (loadCompleted)
			{
				if (isCovered == true)
				{
					assetClip.gotoAndPlay("Closed");
				}
				
				if (isCovered == false)
				{
					assetClip.gotoAndPlay("Open");
				}
			}
		}	
	}
}