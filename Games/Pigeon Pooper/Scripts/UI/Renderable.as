package UI
{	
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	
	public class Renderable extends MovieClip
	{
		public var isFacingRight:Boolean = false;
		
		protected var parentClip:MovieClip; // parent of the base clip
		protected var baseClip:MovieClip; // primary movie clip that all others attacht		
		protected var assetClip:MovieClip; // used to load external assets		
		
		protected var assetWidth:Number;
		protected var assetHeight:Number;
		
		protected var facingModifier:Number = 1; //Facing.		
		protected var loadCompleted:Boolean = false;
		
		public function Renderable(argParentClip:MovieClip, argAssetPath:String, addToParent:Boolean = true)
		{
			parentClip = argParentClip;
			
			// Create the baseClip on the parent
			baseClip = new MovieClip();
			AttachToParent(addToParent);
			
			// Create a loader and load the provided asset path
			var loader:Loader = new Loader();
			loader.load(new URLRequest(argAssetPath));
			loader.contentLoaderInfo.addEventListener(Event.COMPLETE, completedExternalAssetLoad);
		}
		
		public function setX(newX:Number):void  {baseClip.x = newX; }
		
		public function setY(newY:Number):void  {baseClip.y = newY; }
		
		public function getX():Number {return baseClip.x; }
	
		public function getY():Number {return baseClip.y;}

		public function getClip():MovieClip  {return baseClip; }	
		
		public function getAssetClip():MovieClip  {return assetClip; }	
		
		public function FaceRight(faceRight:Boolean):void 
		{
			if (faceRight)
			{
				isFacingRight = true;
				baseClip.scaleX = Math.abs(baseClip.scaleX) * -1;
			}
			else if (!faceRight)
			{
				isFacingRight = false;
				baseClip.scaleX = Math.abs(baseClip.scaleX);
			}
		}
		
		public function AttachToParent(bool:Boolean)
		{
			if (bool)
			{
				if (parentClip != null && !parentClip.contains(baseClip))
				{
					parentClip.addChild(baseClip);
				}				
			}
			else
			{
				if (parentClip != null && parentClip.contains(baseClip))
				{
					parentClip.removeChild(baseClip);
				}
			}
		}
		
		protected function completedExternalAssetLoad(event:Event):void
		{
			loadCompleted = true;
			
			// Assign the movie clip for the asset and center it on the base clip	
			assetClip = MovieClip(event.target.content);
			baseClip.addChild(this.assetClip);
			
			//Cache and position
			assetWidth = assetClip.width;
			assetHeight = assetClip.height;
			assetClip.x -= assetWidth / 2;
			assetClip.y -= assetHeight / 2;
			
			// Remove the event listener that triggered this call back
			event.target.removeEventListener(Event.COMPLETE, this.completedExternalAssetLoad);
			
			LoadComplete();
		}
		
		protected function LoadComplete() {}
	}
}