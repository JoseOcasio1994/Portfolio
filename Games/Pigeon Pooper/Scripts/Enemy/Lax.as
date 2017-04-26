package Enemy
{	
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	
	public class Lax extends EnemyBase
	{				
		private var flipped:Boolean = false;
		private var gravity:Number = .75;
		
		public function Lax(argParentClip:MovieClip)
		{
			super(argParentClip, "Assets/Art/laxative.swf");
			speed = -20;
			points = -50;
		}
		
		public override function MainLoop():void
		{
			baseClip.y += speed;
			speed += gravity;
			
			if (speed > 0 && flipped == false)
			{
				baseClip.scaleY = Math.abs(baseClip.scaleY) * -1;
				flipped = true;
			}		
		}
	}
}