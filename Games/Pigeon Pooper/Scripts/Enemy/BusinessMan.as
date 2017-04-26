package Enemy
{	
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	
	public class BusinessMan extends EnemyBase
	{		
		private var idleTimer:Timer;
		private var walkTimer:Timer;
		var isIdle:Boolean = false;
		
		public function BusinessMan(argParentClip:MovieClip)
		{
			super(argParentClip, "Assets/Art/imgEnemy1.swf");
			
			speed = 5;
			points = 800;
			
			idleTimer = new Timer(1000);
			walkTimer = new Timer(2900);
			walkTimer.start();
			SetStats(mainStage.stageHeight - 115);
		}
		
		protected override function LoadComplete() 
		{
			idleTimer.addEventListener(TimerEvent.TIMER, idleHandler);
			walkTimer.addEventListener(TimerEvent.TIMER, walkHandler);
		}
		
		public function modX():void
		{			
			baseClip.x += speed;
			if (baseClip.x >= (mainStage.stageWidth - (baseClip.width / 2)) && facingRight)
			{
				ChangeDirection(false);
			}
			
			else if (baseClip.x <= (baseClip.width / 2) && !facingRight)
			{
				ChangeDirection(true);
			}
		}
		
		public override function removeSelf():void
		{
			if (!cleanedUp)
			{
				cleanedUp = true;				
				idleTimer.removeEventListener(TimerEvent.TIMER, idleHandler);
				walkTimer.removeEventListener(TimerEvent.TIMER, walkHandler);
				AttachToParent(false);
			}
		}
		
		private function walkHandler(e:TimerEvent):void
		{			
			walkTimer.stop()
			isIdle = true;
			idleTimer.start();		
		}
		
		private function idleHandler(e:TimerEvent):void
		{			
			idleTimer.stop()
			isIdle = false;
			walkTimer.start();
		}
		
		public override function MainLoop():void
		{
			if (loadCompleted)
			{
				if (isIdle)
				{
					assetClip.gotoAndPlay("Clock");				
				}
				else
				{				
					modX();
					if (assetClip.isPlaying == false) 
						assetClip.gotoAndPlay("Walk1");
				}
			}
		}
	}
}