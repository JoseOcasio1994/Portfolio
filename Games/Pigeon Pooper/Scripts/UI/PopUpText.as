package UI
{	
	import flash.display.MovieClip;
	import flash.geom.ColorTransform;
		
	public class PopUpText extends Renderable
	{		
		static var low:uint = 0xb3b3b3;
		static var mid:uint = 0xf2f2f2;
		static var high:uint = 0xffff00;
		static var alphaReduceRate:Number = 0.2;
		static var floatSpeed:Number = 0.8;
		
		var ticksBeforeFade:int = 20;
		var currentTicks:int;
		var displayText:String;
		
		public function PopUpText(argParentClip:MovieClip, argText:String)
		{			
			super(argParentClip, "Assets/PopUp/PopUpPoints.swf");
			displayText = argText;
		}
		
		public function FinishedUpdate ():Boolean
		{
			if (loadCompleted)
			{
				var a:Number = assetClip.alpha;
				if (a <= 0)
				{
					return true;
				}
				
				setY(getY() - floatSpeed);	
					
				if (currentTicks < ticksBeforeFade)
				{
					currentTicks++;
				}
				else
				{
					a -= alphaReduceRate;
					assetClip.alpha = a;
				}
			}
			return false;
		}
		
		protected override function LoadComplete() 
		{
			assetClip.OuterButton.InnerText.text = displayText;
		}
	}
}