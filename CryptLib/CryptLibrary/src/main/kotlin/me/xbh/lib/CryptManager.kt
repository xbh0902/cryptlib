package me.xbh.lib

/**
 * Created by lulu on 17-9-27.
 */
class CryptManager private constructor() {

    init {
        System.loadLibrary("crypt")
    }

    companion object {

        private var INSTANCE : CryptManager? = null

        fun getInstance() : CryptManager{

            if (INSTANCE == null){
                synchronized(CryptManager::class.java){
                    INSTANCE = CryptManager()
                }
            }
            return INSTANCE!!
        }
    }
}