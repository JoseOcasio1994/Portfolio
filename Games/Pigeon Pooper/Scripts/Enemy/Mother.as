package Enemy
{	
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	
	public class Mother extends EnemyBase
	{		
		public var baby:Baby;
		var isRunning:Boolean = false;

		public function Mother(argParentClip:MovieClip)
		{
			super(argParentClip, "Assets/Art/imgMother.swf");
			speed = 5;
			points = 650;
			SetStats(mainStage.stageHeight - 115);
		}

		public override function MainLoop():void
		{
			Move();
			if (baby != null)
			{
				if (facingRight)
				{
					baby.setX(baseClip.x + 45);
				}
				else
				{
					baby.setX(baseClip.x - 45);
				}
			}
			
			if (loadCompleted)
			{
				if (assetClip.isPlaying == false && isRunning == false)
				{
					assetClip.gotoAndPlay("Walk");
				}
				if (assetClip.isPlaying == false && isRunning == true)
				{
					assetClip.gotoAndPlay("Run");
				}
			}
		}
		
		public function Move():void
		{			
			baseClip.x += speed;
			
			if (baby != null)
			{
				if (baseClip.x + 50 >= mainStage.stageWidth - baseClip.width / 2 && facingRight == true)
				{
					ChangeDirection(false);
					baby.ChangeDirection(false);;
				}
				
				else if (baseClip.x - 50 <= baseClip.width / 2 && facingRight == false)
				{
					ChangeDirection(true);
					baby.ChangeDirection(true);
				}
			}			
			else
			{
				if (baseClip.x + 12 >= mainStage.stageWidth - baseClip.width / 2 && facingRight == true)
				{
					ChangeDirection(false);
				}
				
				else if (baseClip.x - 12 <= baseClip.width / 2 && facingRight == false)
				{
					ChangeDirection(true);
				}
			}
		}
		
		public function LostBaby():void
		{
			speed = speed * 4;
			isRunning = true;
			points = 1900;
			baby = null;
		}		
		
		public function AddBaby(argBaby:Baby):void
		{
			baby = argBaby;
		}
		
		public function setPoints(newPoint:int){points = newPoint;}		
	}
}