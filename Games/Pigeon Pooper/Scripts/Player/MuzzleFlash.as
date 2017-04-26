package Player
{	
	import UI.*;
	import Audio.*;
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	import flash.geom.Point;

	public class MuzzleFlash extends Renderable
	{
		public function MuzzleFlash(argParentClip:MovieClip)
		{
			super(argParentClip, "Assets/Player/MuzzleFlash.swf");			
		}
		
		protected override function LoadComplete() 
		{
			assetClip.gotoAndStop(4); //Don't play after spawnning, since this will be attached to the bird.
		}		
	}	
}