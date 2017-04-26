package Player
{	
	import UI.*;
	import Audio.*;
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	import flash.geom.Point;
	
	public class PoopFlatten extends Renderable
	{		
		public function PoopFlatten(argParentClip:MovieClip)
		{
			super(argParentClip, "Assets/Art/PoopFlatten.swf");			
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