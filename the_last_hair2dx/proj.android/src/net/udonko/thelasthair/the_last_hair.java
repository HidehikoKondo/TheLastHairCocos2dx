/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package net.udonko.thelasthair;
import com.google.android.gms.ads.*;

import org.cocos2dx.lib.Cocos2dxActivity;
import net.app_c.cloud.plugin.c2dx.*;

import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.widget.FrameLayout;
import android.widget.LinearLayout;

public class the_last_hair extends AppCCloudActivity{

	private static the_last_hair _activity = null;
	private static AdView adView;
    private final int lp = LinearLayout.LayoutParams.WRAP_CONTENT;
    private static InterstitialAd interstitial;
    private static int playCount;
    
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		
		//プレイ回数の初期化
		playCount = 0;
		
		if (_activity == null) _activity = this;

		//バナー広告
		adView = new AdView(this);
        adView.setAdSize(AdSize.BANNER);
        adView.setAdUnitId("ca-app-pub-3324877759270339/8639463829");
         
        FrameLayout.LayoutParams adParams = new FrameLayout.LayoutParams(lp,lp);
        adParams.gravity = (Gravity.TOP|Gravity.CENTER); 
        addContentView(adView, adParams);
         
        AdRequest adRequest = new AdRequest.Builder().build();
         
        adView.loadAd(adRequest);
        
        loadInterstitialJni();

        
	}
	
	  // インタースティシャルを表示する準備ができたら、displayInterstitial() を呼び出す。
	  public static void displayInterstitial() {

	  }
	  
	public static void tweet(String $msg){
        Intent intent = new Intent();
        intent.setAction(Intent.ACTION_SEND);
        intent.setType("text/plain");
        intent.putExtra(Intent.EXTRA_TEXT, $msg);
        _activity.startActivity(intent);
    }	
    static {
         System.loadLibrary("game");
    }

    public static the_last_hair getActivity() {
        return _activity;
    }
    
    
    public static void showInterstitialJni()
    {
    	Log.d("Interstitial","JNIインタースティシャル showInterstitialJni");
	    //displayInterstitial();
	    
		  _activity.runOnUiThread(new Runnable() {
				@Override
				public void run() {
			    	Log.d("Interstitial","ロード確認！！！！！"+playCount);
					if (interstitial.isLoaded()) {
						//インタースティシャルを２回に１回表示する
				    	Log.d("Interstitial","表示！！！！！"+playCount);
						playCount++;
						if( (playCount%2) == 0 ){
					    	interstitial.show();
						}
				    }
				}
		  });
	}
    
    public static void loadInterstitialJni()
    {
    	Log.d("Interstitial","JNIインタースティシャル loadInterstitialJni");
    	
		  _activity.runOnUiThread(new Runnable() {
				@Override
				public void run() {
		  
		  
        //インタースティシャル
        interstitial = new InterstitialAd(_activity);
        interstitial.setAdUnitId("ca-app-pub-3324877759270339/2174127829");

        // 広告リクエストを作成する。
        AdRequest interstitalAdRequest = new AdRequest.Builder().build();

        // インタースティシャルの読み込みを開始する。
        interstitial.loadAd(interstitalAdRequest);

        interstitial.setAdListener(new AdListener() {
            @Override
            public void onAdLoaded() {
            	Log.d("interstitial","ロード成功");
                //displayInterstitial();
            }
 
            @Override
            public void onAdFailedToLoad(int errorCode) {
            //    String message = String.format("onAdFailedToLoad (%s)", getErrorReason(errorCode));
            	Log.d("interstitial","ロード失敗");
            }
        });

				}
		  });

	}
}
