package me.xbh.cryptlib.ui

import android.databinding.DataBindingUtil
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.util.Log
import kotlinx.android.synthetic.main.activity_main.*
import me.xbh.cryptlib.R
import me.xbh.cryptlib.databinding.ActivityMainBinding
import me.xbh.lib.CryptManager
import me.xbh.lib.Md5
import me.xbh.lib.bean.Type
import me.xbh.lib.impl.AesImpl
import me.xbh.lib.impl.RsaImpl
import java.nio.charset.Charset

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
        Log.i(TAG, "c_md5=>${Md5.digest(text)}")
        var count = 0;
        do {
            Log.i(TAG, "================= RSA-BEGIN =================")
            val pubkey = cm.getRsaPubKey(1)
//        val enstr = cm.encrypt(rsa, "jVIr32Ju5H85laQY", pubkey)
            val destr = cm.decrypt(Type.RSA, "a8JM1DHGc54t13Qlfmd+nQMYbH8aQhVOgYdiUG/4tnu9AUR56+HOXLf701UwJgTbWWgGBzEx5zqhKt4oX5v2Wmb3PsKOh8MX3ByTlgMajrOlpsRLDLfDr+19wIEbro0FdrNlN9Um5WS2iGSO3OIGOGixd53fvSdE4+afqrWiFYg=", pubkey);
//        Log.i(TAG, "encrypt=>$enstr")
            Log.i(TAG, "decrypt=>$destr")
            Log.i(TAG, "pubkey=>$pubkey")
            Log.i(TAG, "================= RSA-END   =================")
            Log.i(TAG, "================= AES-BEGIN =================")
            val key = destr
            val plainText = cm.decrypt(Type.AES,"OLv+3+0UxRQnnuVChX0sy/jIHpA/DMyzeVW+zBqwgLbi/89YTgBG9m0r4h0LfoBLTaXZHOn8VDV2hS1MRSIcDoUED5zMIB7gv08A88WapzCNYgT1Nfb4BxXUi5ys19CSpjWbdGLElqMa7B5XLsl6/DkZn5sZSst2KMy51SFKXpoIFG3n8Np2yA9/SO8yYzU9gqU46ss5cH6tL0vBZ4QpnhfwcgrreUOaH4bM/T56/R4VYfzYDpS/2HK+ete3a4zp23rk2AVEWcSi1vP1JlbMY3u6YqPLDa4Lu0xrPEoPq+S5q4cgBQK2dVulgpAk3pnm", key)
            Log.i(TAG, "decrypt=>$plainText")
            Log.i(TAG, "AESLOCALKEY=>${cm.getAesLocalKey(this)}")
            Log.i(TAG, "================= AES-END   =================")

            count++
        } while (count < 0)
    }

}