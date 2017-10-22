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
import me.xbh.lib.impl.AesImpl
import me.xbh.lib.impl.RsaImpl
import java.nio.charset.Charset

/**
 * Created by lulu on 17-9-27.
 */
class MainActivity : AppCompatActivity() {

    val TAG = "Test"
    lateinit var binding : ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = DataBindingUtil.setContentView(this, R.layout.activity_main)



    }

    override fun onResume() {
        super.onResume()
        val text = "{name:\"你好啊，我不好！你真的ok吗？\", age:120}"
        val cm = CryptManager
        Log.i(TAG, "c_md5=>${Md5.digest(text)}")

        val aes = AesImpl();
        val key = cm.getKey(aes, null)
        val cipherText = aes.encrypt(text, key)
        val plainText = aes.decrypt(cipherText, key)
        Log.i(TAG, "encrypt=>$cipherText")
        Log.i(TAG, "decrypt=>$plainText")
        Log.i(TAG, "key=>$key")

        Log.i(TAG, "================= RSA-BEGIN =================")
        val rsa = RsaImpl()
        val pubkey = cm.getKey(rsa, 1)
        val enstr = cm.encrypt(rsa, "jVIr32Ju5H85laQY", pubkey)
        val destr = cm.decrypt(rsa, "", pubkey);
        Log.i(TAG, "encrypt=>$enstr")
        Log.i(TAG, "decrypt=>$destr")
        Log.i(TAG, "pubkey=>$pubkey")
        Log.i(TAG, "================= RSA-END   =================")
    }

}