package
{	
	import flash.display.MovieClip;
	
	public class PickUpTextBase extends MovieClip
	{
		protected static var alphaReduceRate:Number = 0.2;
		protected static var floatSpeed:Number = 0.8;
		protected var ticksBeforeFade:int = 20;
		protected var currentTicks:int;
		
		public function PickUpTextBase ()
		{
			
			MainManager.UIFGLayer.addChild(this);
		}
		
		public function AttachToParent (isTrue:Boolean)
		{
			if (isTrue)
			{
				MainManager.UIFGLayer.addChild(this);
			}
			else
			{
				MainManager.UIFGLayer.removeChild(this);
			}
		}
		
		public function FinishedUpdate ():Boolean
		{
			if (alpha <= 0)
			{
				return true;
			}
			
			y = y - floatSpeed;
				
			if (currentTicks < ticksBeforeFade)
			{
				currentTicks++;
			}
			else
			{
				alpha -= alphaReduceRate;
			}
			return false;
		}
	}
}