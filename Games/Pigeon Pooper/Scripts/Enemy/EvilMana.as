package Enemy
{
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	
	public class EvilMana extends EnemyBase
	{
		public function EvilMana(argParentClip:MovieClip)
		{
			super(argParentClip, "Assets/Art/Animations/Elderly/EvilmamaWalk/BadGrandmaWalk.swf");
			speed = 3;
			points = 650;
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