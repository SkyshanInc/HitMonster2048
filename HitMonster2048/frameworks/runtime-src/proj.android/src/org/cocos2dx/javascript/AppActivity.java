/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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
package org.cocos2dx.javascript;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import com.friendou.Interface.coralsdk;

import android.os.Bundle;
import android.os.StrictMode;
import android.view.KeyEvent;


public class AppActivity extends Cocos2dxActivity {
	Cocos2dxGLSurfaceView mCocos2dxGLSurfaceView = null;
	@Override
    public Cocos2dxGLSurfaceView onCreateView() {
		mCocos2dxGLSurfaceView = new Cocos2dxGLSurfaceView(this);
        // TestCpp should create stencil buffer
		mCocos2dxGLSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);

        return mCocos2dxGLSurfaceView;
    }
	protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        if (android.os.Build.VERSION.SDK_INT > 9) {
            StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build(); StrictMode.setThreadPolicy(policy);
        }
        coralsdk.init(this);
    }
	public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        if(mCocos2dxGLSurfaceView != null)
        {
            mCocos2dxGLSurfaceView.onKeyDown(keyCode, event);
        }
        return super.onKeyDown(keyCode, event);
    }
}
