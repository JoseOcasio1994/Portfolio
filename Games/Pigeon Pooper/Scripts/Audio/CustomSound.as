package Audio
{	
	import flash.media.Sound;
	import flash.net.URLRequest;
	import flash.media.SoundChannel;
	
	public class CustomSound
	{		
		private var sound:Sound = new Sound();
		private var soundChannel:SoundChannel = new SoundChannel();
		
		public function CustomSound(soundArg:String, loop:int)
		{
			var request:URLRequest = new URLRequest(soundArg);
			sound.load(request);
			soundChannel = sound.play(0, loop);
		}
		
		public function stop():void  
		{ 
			soundChannel.stop(); 
		}	
	}
}