package me.xbh.lib

import me.xbh.lib.impl.AesImpl


/**
 * Created by lulu on 17-9-27.
 */
object CryptManager{

    init {
        System.loadLibrary("crypt")
    }

    fun getKey(crypt: ICrypt, obj: Any?): String{
        if (crypt is AesImpl){
            return crypt.getKey(null)
        }else{
            return crypt.getKey(obj)
        }
    }

    fun encrypt(crypt: ICrypt, plain: String, key: String): String = crypt.encrypt(plain, key)


    fun decrypt(crypt: ICrypt, cipher: String, key: String): String = crypt.encrypt(cipher, key)
}