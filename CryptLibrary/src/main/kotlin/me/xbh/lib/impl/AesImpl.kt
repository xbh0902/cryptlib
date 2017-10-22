package me.xbh.lib.impl

import me.xbh.lib.ICrypt


/**
 * Created by lulu on 17-9-27.
 */
class AesImpl : ICrypt{


   override fun getKey(obj: Any?): String = getRandomKey()

   override fun encrypt(plain: String, key: String): String = encode(plain, key)

   override fun decrypt(cipher: String, key: String): String = decode(cipher, key)

   /**
    * 获取随机16位密钥
    */
   external fun getRandomKey() : String

   /**
    * 加密
    */
   external fun encode(plainText : String, key: String) : String

   /**
    * 解密
    */
   external fun decode(cipherText : String, key: String) : String

}