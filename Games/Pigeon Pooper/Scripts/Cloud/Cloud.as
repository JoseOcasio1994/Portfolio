package Cloud
{	
	import UI.*;
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.net.URLRequest;
	
	public class Cloud extends Renderable
	{
		private var goingLeft = false;
		private var speed:Number = 2;
		private var mainstage:Stage;
		
		public function Cloud(argParentClip:MovieClip)
		{
			mainstage = argParentClip.stage;
			
			var path:String;
			switch(Math.floor(Math.random() * 3))
			{
				case 0:
					path = "Assets/Art/Cloud01.swf";
					break;
				case 1:
					path = "Assets/Art/Cloud02.swf";
					break;
				default: 
					path = "Assets/Art/Cloud03.swf";
					break;
			}
			super (argParentClip, path, true);
						
			goingLeft = Boolean(Math.floor(Math.random() * 2));
			if (goingLeft)
			{				
				setX(mainstage.stageWidth + 100);
				speed = -speed;
			}
			else
			{
				setX(-100);
			}
			setY(40);
		}
		
		public function MainLoop():void
		{
			baseClip.x += speed;
			
			if (baseClip.x > mainstage.stageWidth + 100 && !goingLeft)
				CleanUp();
			
			if (baseClip.x < -100 && goingLeft)
				CleanUp();
		}
		
		public function CleanUp():void
		{
			AttachToParent(false);
		}
	}
}