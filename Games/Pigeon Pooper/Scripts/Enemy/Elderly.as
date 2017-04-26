package Enemy
{
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	
	public class Elderly extends EnemyBase
	{
		public function Elderly(argParentClip:MovieClip)
		{
			super(argParentClip, "Assets/Art/imgElderly.swf");
			speed = 3;
			points = 950;
			flipX = true;
			SetStats(mainStage.stageHeight - 110);
		}
		
		public function modX():void
		{
			baseClip.x += speed;
			
			if (baseClip.x >= mainStage.stageWidth - baseClip.width / 2 && facingRight == true)
				ChangeDirection(false);
			
			else if (baseClip.x <= baseClip.width / 2 && facingRight == false)
				ChangeDirection(true);
		}
		
		public override function MainLoop():void  { modX(); }
	}
}