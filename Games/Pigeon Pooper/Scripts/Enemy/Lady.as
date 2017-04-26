package Enemy
{	
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	
	public class Lady extends EnemyBase
	{				
		public function Lady(argParentClip:MovieClip)
		{
			super(argParentClip, "Assets/Art/imgLady.swf");
			speed = 4;
			points = 0;
			flipX = true;
			SetStats(mainStage.stageHeight - 125);
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