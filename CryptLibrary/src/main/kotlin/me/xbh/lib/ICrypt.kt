package me.xbh.lib

/**
 * 加密接口
 */
interface ICrypt {

    fun getKey(obj : Any): String

    fun encrypt(plain: String, key: String): String

    fun decrypt(cipher: String, key: String): String

}