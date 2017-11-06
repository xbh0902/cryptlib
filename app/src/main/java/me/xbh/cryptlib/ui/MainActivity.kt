package me.xbh.cryptlib.ui

import android.databinding.DataBindingUtil
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.util.Log
import me.xbh.cryptlib.R
import me.xbh.cryptlib.databinding.ActivityMainBinding
import me.xbh.lib.CryptManager

/**
 * Created by lulu on 17-9-27.
 */
class MainActivity : AppCompatActivity() {

    val TAG = "Test"
    lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = DataBindingUtil.setContentView(this, R.layout.activity_main)


    }

    override fun onResume() {
        super.onResume()
        val text = "{name:\"你好啊，我不好！你真的ok吗？\", age:120}"
        val cm = CryptManager
        Log.i(TAG, "c_md5=>${cm.md5(text)}")
        var count = 0;
        do {
            Log.i(TAG, "================= RSA-BEGIN =================")
            val pubkey = cm.getRsaPubKey(1)
//        val enstr = cm.encrypt(rsa, "jVIr32Ju5H85laQY", pubkey)
            val destr = cm.decrypt(CryptManager.Type.RSA, "Y7R1J829EraGPqBXdXVDRD65X943eKtvhp33kmoXNFAfH15qdFv8b3JySyyT+3ZjU2j3Nn3zaQUTX6V9C8zoeQvBYEN3FK7bVWwPwGBTkJ5Uw6+sthZUfWCqPZWFLtvSM3qOJymmcvaNPu648/V99RI4Sx3J/2vQQzIdorcrDKY=", pubkey);
//        Log.i(TAG, "encrypt=>$enstr")
            Log.i(TAG, "decrypt=>$destr")
            Log.i(TAG, "pubkey=>$pubkey")
            Log.i(TAG, "================= RSA-END   =================")
            Log.i(TAG, "================= AES-BEGIN =================")
            val key = destr
            val plainText = cm.decrypt(CryptManager.Type.AES,"/BBBv9p/VGs5P9hBvCUHzok3hpJ+f8pVE2VbeYkMjJLGMw5igBtav58JN9NJilYVgJzCIrKfm618" +
                    "P1ovtJueYh5Y4gaewftOsPP3PwsBPoORpADFiI8ttVPEbRextUjCgE7uVUkUAftomE9eFeAdbGRv" +
                    "jqeot7B6eCHeIIPFbOo+ZOCk7uX36UiT0tNXcu+hh3ezuOXrSsgi5a/Io++xSRsUEAgcj3JY+UHe" +
                    "h4Ig2WFgaFOnOtjeWl/LHE4A7ww9qK11ONsgb7q6I1LfFwNjNWpSeerbOLkbJCwfnP1yW2gVvwwL" +
                    "GmMvQ1wFgZNBwYAs", key)
            Log.i(TAG, "decrypt=>$plainText")
            Log.i(TAG, "AESLOCALKEY=>${cm.getAesLocalKey(this)}")
            Log.i(TAG, "================= AES-END   =================")
            count++

        } while (count < 0)


    }

}