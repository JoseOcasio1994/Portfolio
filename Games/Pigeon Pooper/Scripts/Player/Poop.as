package Player
{	
	import UI.*;
	import Audio.*;
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	import flash.geom.Point;
	
	public class Poop extends Renderable
	{
		public var Reflected:Boolean = false;
		private var speed:Number = 4;
		
		private var cleanedUp:Boolean = false;
		
		public function Poop(argParentClip:MovieClip)
		{
			super(argParentClip, "Assets/Player/imgPoop.swf");			
		}

		public function MainLoop():Boolean
		{	
			//Physics and destroy.
			if (baseClip.y > 310)
			{
				CleanUp ();
				AudioManager.PlayPoopSplat();
				return true;
			}
			else
			{
				//Move
				baseClip.y += speed;
				speed = speed + 0.75;
				return false;
			}
		}	
		
		public function CleanUp ()
		{
			if (!cleanedUp)
			{
				cleanedUp = true;		
				
				//Hide object
				if (parentClip != null)
				{		
					AttachToParent(false);
				}
			}
		}
		
		public function SetSpeed (newSpeed:int)
		{
			speed = newSpeed;
		}		
	}
}