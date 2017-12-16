package me.xbh.lib.core.cxx

import me.xbh.lib.core.ICrypt

/**
* <p>
* 描述：RSA加密本地接口
* </p>
* 创建日期：2017年11月02日.
* @author wenbin.zhou@ehking.com
* @version 1.0
*/
internal open class RsaImpl : ICrypt {

    override fun getKey(obj: Any?): String = getPublicKey(obj as Int)

    override fun encrypt(plain: String, key: String): String = encryptByPublicKey(plain, key)

    override fun decrypt(cipher: String, key: String): String = decryptByPublicKey(cipher, key)

    external fun getPublicKey(int: Int): String

    external fun encryptByPublicKey(plain: String, key: String): String

    external fun decryptByPublicKey(cipher: String, key: String): String
}