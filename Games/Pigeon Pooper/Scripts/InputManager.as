

package {
	
	import flash.display.MovieClip;
	import flash.events.KeyboardEvent;
	import flash.ui.Keyboard;
	
	public class InputManager 
	{
		private var targetObject:MovieClip;
		private var facingRight:Boolean = true;
		
		public function InputManager(targetObject:MovieClip) 
		{
			this.targetObject = targetObject;
		}		
		
		public function handleKeyDown(keyEvent:KeyboardEvent):void 
		{
			var moveDistance:Number = 10; // establish a consistent distance to move the target object
			
			// Respond to specific keyboard keys
			if (keyEvent.keyCode == Keyboard.UP) { this.targetObject.modY(-moveDistance); }
			else if (keyEvent.keyCode == Keyboard.DOWN) { this.targetObject.modY(moveDistance); }
			else if (keyEvent.keyCode == Keyboard.LEFT || keyEvent.keyCode == Keyboard.A) 
			{ 	
				this.targetObject.modX( -moveDistance);
			}
					
			else if (keyEvent.keyCode == Keyboard.RIGHT|| keyEvent.keyCode == Keyboard.D) 
			{ 
				this.targetObject.modX( +moveDistance); 
			}
		}
		
	}
	
}
