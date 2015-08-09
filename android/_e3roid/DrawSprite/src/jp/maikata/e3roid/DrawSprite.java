package jp.maikata.e3roid;

import android.view.MotionEvent;

import com.e3roid.E3Activity;
import com.e3roid.E3Engine;
import com.e3roid.E3Scene;
import com.e3roid.drawable.Sprite;
import com.e3roid.drawable.sprite.TextSprite;
import com.e3roid.drawable.texture.Texture;
import com.e3roid.drawable.texture.AssetTexture;


public class DrawSprite extends E3Activity
{
	private final static int WIDTH  = 320;
	private final static int HEIGHT = 480;
	
	private Sprite		robot;
	private TextSprite	score;
	private Texture		robotTexture;

	private	Integer		count	= 0;

	@Override
	public E3Engine onLoadEngine() {
		E3Engine engine = new E3Engine(this, WIDTH, HEIGHT);

		engine.requestFullScreen();
//		engine.requestPortrait();
		engine.requestLandscape();

		return engine;
	}

	@Override
	public E3Scene onLoadScene() {
		E3Scene scene = new E3Scene();
		scene.addEventListener(this);

//		score.move((getWidth() - score.getWidth()) / 2, (getHeight() - score.getHeight()) / 2);
		score.move((getWidth() - score.getWidth()) * 2 / 3, (getHeight() - score.getHeight()) * 2 / 3);
		
		int centerX = (getWidth()  - robotTexture.getWidth())  / 2;
		int centerY = (getHeight() - robotTexture.getHeight()) / 2;
		
		robot = new Sprite(robotTexture, centerX, centerY);

		scene.getTopLayer().add(score);
		scene.getTopLayer().add(robot);

		return scene;
	}

	@Override
	public void onLoadResources() {
		robotTexture = new AssetTexture("robot.png", this);

		score = new TextSprite("score = XX", 18, this);
	}

	@Override
	public boolean onSceneTouchEvent(E3Scene scene, MotionEvent motionEvent) {
		if (robot != null) {
			// robot rotates and scales when touchEvent ACTION_DOWN occurs.
			if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
				robot.rotate(robot.getAngle() + 20.0f,
							 (robotTexture.getWidth()  / 2),
							 (robotTexture.getHeight() / 2));
				robot.scale(robot.getScaleX() + 0.2f,
							robot.getScaleY() + 0.2f,
							(robotTexture.getWidth()  / 2),
							(robotTexture.getHeight() / 2));

				count	= count + 1;
				score.setText(String.format("score = %d", count.intValue()));
			
				if (!score.isVisible()) {
					score.show();
				}
			}
		}

		return false;
	}
}
