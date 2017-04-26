package Player.Control
{	
	import Player.*;
	import UI.*;
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
	
	public class MouseControl extends PlayerControlScheme
	{		
		var poopTimer:Timer;
		
		//Move lerp
		var lerpSpeed:Number = 0.3;
		
		//Facing
		var previousX:Number = 0;
		
		public function MouseControl(argStage:Stage, argBird:Bird, argPoopCallback:Function)
		{
			super(argStage, argBird, argPoopCallback);
			poopTimer = new Timer(MainManager.GetPoopIntervals());
			mainStage.addEventListener(MouseEvent.MOUSE_DOWN, StartPoopTimer);
			mainStage.addEventListener(MouseEvent.MOUSE_UP, StopPoopTimer);
			poopTimer.addEventListener(TimerEvent.TIMER, PoopTimerUp);
		}
		
		public override function MainLoop()
		{
			if (!isStunned && !isPaused)
			{				
				//Get mouse position
				var stageMouseX = mainStage.mouseX;
				if (stageMouseX > maxStageX)
				{					
					stageMouseX = maxStageX;
				}
				else if (stageMouseX < minStageX)
				{
					stageMouseX = minStageX;
				}
				
				//Lerp
				var curX = bird.getX();
				var tgtX = curX + (stageMouseX - curX) * lerpSpeed;
				
				//Mouse rel position
				var relRange:Number = stageCenterX - minStageX;
				var relXFromCenter = stageMouseX - stageCenterX;
				var relRatio:Number = relXFromCenter / relRange;
				//trace("relRatio: " + relRatio);
				UIManager.Parallax(relRatio, 3);
				
				//Move		
				bird.setX(tgtX);
				
				//Facing
				var xDiff : Number = mainStage.mouseX - previousX;
				if (!bird.isFacingRight && xDiff > 0)
				{
					bird.FaceRight(true);
				}
				else if (bird.isFacingRight && xDiff < 0)
				{
					bird.FaceRight(false);
				}
				
				previousX = mainStage.mouseX;
			}
		}
		
		public override function CleanUp ()
		{
			mainStage.removeEventListener(MouseEvent.MOUSE_DOWN, StartPoopTimer);
			mainStage.removeEventListener(MouseEvent.MOUSE_UP, StopPoopTimer);
			poopTimer.removeEventListener(TimerEvent.TIMER, PoopTimerUp);
		}
		
		public override function StunStarted ()
		{
			poopTimer.stop();
			poopTimer.reset();
			isStunned = true;
		}
		
		public override function StunFinished ()
		{
			isStunned = false;
		}
		
		function StartPoopTimer (event:MouseEvent) 
		{
			if (!isStunned && !isPaused)
			{
				poopTimer.start();
				if (poopCallback != null)
				{
					bird.CanPoopCheck();
				}	
			}
		}
		
		function StopPoopTimer (event:MouseEvent) 
		{
			poopTimer.stop();
			poopTimer.reset();
		}
		
		function PoopTimerUp (event:TimerEvent)
		{
			poopCallback();			
		}
	}
}