package Player.Control
{	
	import Player.*;
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.net.URLRequest;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.ui.Keyboard;
	import flash.events.TimerEvent;
	import flash.utils.Timer
	
	public class LaxativeControl extends PlayerControlScheme
	{				
		var speed:int = 20;
				
		public function LaxativeControl(argStage:Stage, argBird:Bird, argPoopCallback:Function)
		{
			super(argStage, argBird, argPoopCallback);
		}
		
		public override function MainLoop()
		{
			var newX:Number = 0;
			if (bird.isFacingRight)
			{
				newX = bird.getX() + speed;
				if (newX > mainStage.stageWidth - 20)
				{
					newX = mainStage.stageWidth - 20;
				}
			}
			else
			{
				newX = bird.getX() - speed;
				if (newX < 20)
				{
					newX = 20;
				}
			}
			
			bird.setX(newX);
		}
		
		public override function CleanUp ()
		{
			
		}
	}
}