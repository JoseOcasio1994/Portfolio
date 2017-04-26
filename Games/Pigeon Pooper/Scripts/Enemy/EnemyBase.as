package Enemy
{	
	import UI.*;
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.net.URLRequest;
	
	public class EnemyBase extends Renderable
	{
		public var facingRight:Boolean = true;
		
		protected var mainStage:Stage;
		protected var speed:Number;
		protected var points:int = 100;
		protected var cleanedUp:Boolean = false;
		protected var flipX:Boolean = false;
		
		//Properties
		public function getPoints():int  { return points; }
		
		public function EnemyBase(argParentClip:MovieClip, argAssetPath:String)
		{
			super(argParentClip, argAssetPath, true);
			mainStage = argParentClip.stage;
		}
		
		public function Pause (isTrue:Boolean)
		{
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
		
		protected function SetStats(yPos:Number):void
		{
			setY(yPos);
			
			var spawnLeft:Boolean = Boolean(Math.floor(Math.random() * 2));
			if (spawnLeft)
			{
				setX(-30); //30 is a rough estimate of assetClip().width / 2.
				ChangeDirection(true);
			}
			else
			{
				setX(mainStage.stageWidth + 30);
				ChangeDirection(false);
			}
		}

		public function removeSelf():void
		{
			if (!cleanedUp)
			{
				cleanedUp = true;
				AttachToParent(false);						
			}
		}

		public function MainLoop():void  {}
		
		public function ChangeDirection (toRight:Boolean)
		{
			if (toRight)
			{
				facingRight = true;
				if (flipX)
				{
					baseClip.scaleX = -Math.abs(baseClip.scaleX);
				}
				else
				{
					baseClip.scaleX = Math.abs(baseClip.scaleX);
				}
				
				speed = Math.abs(speed);
			}
			else
			{
				facingRight = false;
				if (flipX)
				{
					baseClip.scaleX = Math.abs(baseClip.scaleX);
				}
				else
				{
					baseClip.scaleX = -Math.abs(baseClip.scaleX);
				}
				speed = Math.abs(speed)* -1;
			}
		}
	}	
}