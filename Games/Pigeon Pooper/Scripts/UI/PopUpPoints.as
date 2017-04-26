package UI
{	
	import flash.display.MovieClip;
	import flash.geom.ColorTransform;
		
	public class PopUpPoints extends Renderable
	{		
		static var low:uint = 0xb3b3b3;
		static var mid:uint = 0xf2f2f2;
		static var high:uint = 0xffff00;
		static var alphaReduceRate:Number = 0.2;
		static var floatSpeed:Number = 0.8;
		
		var ticksBeforeFade:int = 20;
		var currentTicks:int;
		var displayPoints:int;
		
		public function PopUpPoints(argParentClip:MovieClip, argPoints:int)
		{			
			super(argParentClip, "Assets/PopUp/PopUpPoints.swf");
			displayPoints = argPoints;
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
			var colorTrans:ColorTransform = new ColorTransform();
			if (displayPoints < 600)
			{
				colorTrans.color = low;
			}
			else if (displayPoints < 1100)
			{
				colorTrans.color = mid;
			}
			else
			{
				colorTrans.color = high;				
			}			
			MovieClip(assetClip.getChildAt(0)).getChildAt(1).transform.colorTransform = colorTrans;
			
			assetClip.OuterButton.InnerText.text = displayPoints;
			//trace("children: " + assetClip.numChildren);			
			//trace("assetClip.getChildAt[0]: " + assetClip.getChildAt(0).name);
			//trace("MovieClip(assetClip.getChildAt(0)).numChildren: " + 
			//MovieClip(assetClip.getChildAt(0)).numChildren);
			//trace("MovieClip(assetClip.getChildAt(0)).getChildAt(0).name: " + 
			//MovieClip(assetClip.getChildAt(0)).getChildAt(0).name);
			//trace("MovieClip(assetClip.getChildAt(0)).getChildAt(1).transform.colorTransform.color: " + 
			//MovieClip(assetClip.getChildAt(0)).getChildAt(1).transform.colorTransform);
			//trace("assetClip.OuterButton.InnerText: " + 
			//assetClip.OuterButton.InnerText);
			//trace("assetClip.OuterButton.InnerText.text: " + 
			//assetClip.OuterButton.InnerText.text);
			//assetClip.InnerText.text = points;
		}
	}
}