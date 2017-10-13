package me.xbh.lib.impl

import me.xbh.lib.ICrypt
import java.util.*

/**
 * Created by lulu on 17-10-13.
 */
class RsaImpl : ICrypt {

    override fun getKey(obj: Any): String = getPublicKey(obj as Int)

    override fun encrypt(plain: String, key: String): String = encryptByPublicKey(plain, key)

    override fun decrypt(cipher: String, key: String): String = decryptByPublicKey(cipher, key)

    external fun getPublicKey(int: Int): String

    external fun encryptByPublicKey(plain: String, key: String): String

    external fun decryptByPublicKey(cipher: String, key: String): String
}