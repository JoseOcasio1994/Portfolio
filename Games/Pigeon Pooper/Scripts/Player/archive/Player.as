package Player
{
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	import flash.events.KeyboardEvent;
	import flash.ui.Keyboard;
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	
	public class Player extends MovieClip
	{
		
		private var baseClip:MovieClip; // primary movie clip that all others attach to
		private var parentClip:MovieClip; // parent of the base clip
		private var assetClip:MovieClip; // used to load external assets
		private var facingRight:Boolean = true;
		public var stunned:Boolean = false;
		private var speed:Number = 10;
		
		public function Player(argParentClip:MovieClip)
		{
			this.parentClip = argParentClip;
			
			// Create the base clip on the parent
			this.baseClip = new MovieClip();
			this.parentClip.addChild(this.baseClip);
			
			// Create a loader and load the provided asset path
			var loader:Loader = new Loader();
			loader.load(new URLRequest("Assets/Player/imgPlayer.swf"));
			loader.contentLoaderInfo.addEventListener(Event.COMPLETE, this.completedExternalAssetLoad);
		}
		
		private function completedExternalAssetLoad(event:Event):void
		{
			// Assign the movie clip for the asset and center it on the base clip	
			this.assetClip = MovieClip(event.target.content);
			this.baseClip.addChild(this.assetClip);
			this.assetClip.x -= this.assetClip.width / 2;
			this.assetClip.y -= this.assetClip.height / 2;
			
			// Remove the event listener that triggered this call back
			event.target.removeEventListener(Event.COMPLETE, this.completedExternalAssetLoad);
			// Start Mainloop
			addEventListener(Event.ENTER_FRAME, mainLoop);
		}
		
		public function setX(newX:Number):void  { this.baseClip.x = newX; }
		
		public function setY(newY:Number):void  { this.baseClip.y = newY; }
		
		public function setSpeed(newSpeed:Number):void  { speed = Math.abs(newSpeed); }
		
		public function setStun(isStunned:Boolean):void  { this.stunned = isStunned; }
		
		public function modX():void
		{
			
			if (this.facingRight == true && this.parentClip.mouseX < this.baseClip.x)
			{
				this.flipX();
			}
			
			else if (this.facingRight == false && this.parentClip.mouseX > this.baseClip.x)
			{
				this.flipX();
			}
			
			if (this.parentClip.mouseX - this.baseClip.x >= speed)
				this.baseClip.x += speed;
			
			else if (this.parentClip.mouseX - this.baseClip.x <= -speed)
				this.baseClip.x -= speed;
			
			else if (Math.abs(this.parentClip.mouseX - this.baseClip.x) < speed)
				this.baseClip.x = this.parentClip.mouseX;
		}
		
		public function getClip():MovieClip  { return this.baseClip; }
		
		public function getAsset():MovieClip  { return this.assetClip; }
		
		private function mainLoop(e:Event):void
		{
			if (this.stunned == false)
			{stunned
				modX();
				if (this.assetClip.isPlaying == false)
				{
					this.assetClip.gotoAndPlay("Fly");
				}
			}
			
			if (this.stunned == true && this.assetClip.isPlaying == false)
			{
				this.assetClip.gotoAndPlay("Stun");
			}
		}
		
		public function removeSelf():void
		{
			removeEventListener(Event.ENTER_FRAME, mainLoop);
			this.parent.removeChild(this.baseClip);
			this.parent.removeChild(this);
		}
		
		public function flipX():void
		{
			this.baseClip.scaleX *= -1;
			this.facingRight = !this.facingRight;
		}
	}
}