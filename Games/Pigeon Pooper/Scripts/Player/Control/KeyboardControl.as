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
	
	public class KeyboardControl extends PlayerControlScheme
	{		
		var poopTimer:Timer;
		
		//Move lerp
		var lerpRate:Number = 0.3;
		var maxSpeed:Number = 10;
		var leftAxis:Number = 0;
		var rightAxis:Number = 0;
		var curVel:Number = 0;
		var firstKeyDown:Boolean = false;		
		
		public function KeyboardControl(argStage:Stage, argBird:Bird, argPoopCallback:Function)
		{
			super(argStage, argBird, argPoopCallback);
			poopTimer = new Timer(MainManager.GetPoopIntervals());
			mainStage.addEventListener(KeyboardEvent.KEY_DOWN, KeyDown);
			mainStage.addEventListener(KeyboardEvent.KEY_UP, KeyUp);
			poopTimer.addEventListener(TimerEvent.TIMER, PoopTimerUp);
		}
		
		public override function MainLoop()
		{
			if (!isStunned)
			{
				//Execute movement.
				var tgtVel:Number = leftAxis + rightAxis;
				curVel = curVel + ((tgtVel - curVel) * lerpRate);
				var tgtX:Number = bird.getClip().x + curVel;			
				if (tgtX > maxStageX)
				{
					tgtX = maxStageX;
				}
				else if (tgtX < minStageX)
				{
					tgtX = minStageX;
				}
				bird.setX(tgtX);
				
				var relRange:Number = stageCenterX - minStageX;
				var relXFromCenter = tgtX - stageCenterX;
				var relRatio:Number = relXFromCenter / relRange;
				//trace("relRatio: " + relRatio);
				UIManager.Parallax(relRatio, 5);
				
				//Facing
				if (curVel > 0)
				{
					bird.FaceRight(true);
				}
				else if (curVel < 0)
				{
					bird.FaceRight(false);
				}
			}			
		}
		
		public override function CleanUp ()
		{
			mainStage.removeEventListener(KeyboardEvent.KEY_DOWN, KeyDown);
			mainStage.removeEventListener(KeyboardEvent.KEY_UP, KeyUp);
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
		
		function KeyDown (event:KeyboardEvent) 
		{
			if (event.keyCode == Keyboard.SPACE && !isPaused)
			{
				if (!isStunned)
				{
					poopTimer.start();
					if (!firstKeyDown)
					{
						firstKeyDown = true;
						poopCallback();
					}
				}
			}
			
			if ((event.keyCode == Keyboard.A) ||
				(event.keyCode == Keyboard.LEFT))
			{
				leftAxis = -maxSpeed;
			}
			
			if ((event.keyCode == Keyboard.D) ||
				(event.keyCode == Keyboard.RIGHT))
			{
				rightAxis = maxSpeed;
			}			
		}
		
		function KeyUp (event:KeyboardEvent) 
		{
			if (event.keyCode == Keyboard.SPACE)
			{
				poopTimer.stop();
				poopTimer.reset();
				firstKeyDown = false;
			}
			
			if ((event.keyCode == Keyboard.A) ||
				(event.keyCode == Keyboard.LEFT))
			{
				leftAxis = 0;
			}
			
			if ((event.keyCode == Keyboard.D) ||
				(event.keyCode == Keyboard.RIGHT))
			{
				rightAxis = 0;
			}
		}
		
		function PoopTimerUp (event:TimerEvent)
		{
			poopCallback();
		}
	}
}