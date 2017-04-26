package Player
{	
	import UI.*;
	import Audio.*;
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	import flash.geom.Point;
	
	public class PoopCrumbs extends Renderable
	{		
		var finished:Boolean = false;
		
		var yVel:Number;
		var initialMaxForce:Number = 10;
		var sidewaysMaxForce:Number = 5;
		var gravity:Number = 0.75;
		var sideways:Number;
		var heightTestDeviation:Number = 20;
		var heightTest:Number = 325;
		
		public function PoopCrumbs()
		{
			var dir:String;
			if (Math.floor(Math.random() * 2) >= 1)
			{
				dir = "Assets/Art/PoopDroping.swf";
				heightTest += (Math.random() * heightTestDeviation);
			}
			else
			{
				dir = "Assets/Art/PoopDroping1.swf";
				heightTest -= (Math.random() * heightTestDeviation);
			}
			
			super(MainManager.NonNPCLayer, dir);
			
			yVel = -(Math.random() * initialMaxForce) - initialMaxForce * 0.5;
			sideways = (Math.random() * sidewaysMaxForce * 2) - sidewaysMaxForce;
		}
		
		public function MainLoop ()
		{
			//Physics and destroy.
			if (!finished)
			{
				if (baseClip.y > heightTest)
				{
					finished = true;
				}
				else
				{
					yVel += gravity;
					
					//Move
					baseClip.x += sideways;
					baseClip.y += yVel;
				}
			}
		}
		
		public function CleanUp ()
		{
			if (parentClip != null)
			{		
				AttachToParent(false);
			}
		}	
	}
}