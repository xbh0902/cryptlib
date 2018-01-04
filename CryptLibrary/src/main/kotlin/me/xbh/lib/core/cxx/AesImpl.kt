package me.xbh.lib.core.cxx

import android.content.Context
import me.xbh.lib.core.ICrypt


/**
* <p>
* 描述：AES加密本地接口
* </p>
* 创建日期：2017年11月02日.
* @author wenbin.zhou@ehking.com
* @version 1.0
*/
internal open class AesImpl : ICrypt {


    override fun getKey(obj: Any?): String = if (obj == null) {
        getRandomKey()
    } else {
        getLocalKey(obj as Context)
    }

    override fun encrypt(plain: String, key: String): String = encode(plain, key)

    override fun decrypt(cipher: String, key: String): String = decode(cipher, key)

    /**
     * 获取随机16位密钥
     */
    external fun getRandomKey(): String

    /**
     * 获取本地密钥
     */
    external fun getLocalKey(context: Context): String

    /**
     * 加密
     */
    external fun encode(plainText: String, key: String): String

    /**
     * 解密
     */
    external fun decode(cipherText: String, key: String): String

}