package me.xbh.lib.impl



/**
 * Created by lulu on 17-9-27.
 */
class AesImpl{

   /**
    * 获取随机16位密钥
    */
   external fun getRandomKey() : String

   /**
    * 加密
    */
   external fun encrypt(plainText : String, key: String) : String

   /**
    * 解密
    */
   external fun decrypt(cipherText : String, key: String) : String

}