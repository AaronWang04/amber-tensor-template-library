template<typename Device>
struct Stream {
  // this is only a dummy implementation for CPU
  // for GPU, the actual implementation will be specialized in tensor_gpu-inl.h
  /*!
   * \brief wait for all the computations associated
   *  with this stream to complete
   */
  inline void Wait(void) {}
  /*!
   * \brief query whether the the stream is idle
   * \return true if the stream is idle and all the jobs have been completed
   */
  inline bool CheckIdle(void) {
    return true;
  }
  /*! \brief create a blas handle */
  inline void CreateBlasHandle() {}
};

struct cpu {
  /*! \brief whether this device is CPU or not */
  static const bool kDevCPU = true;
  /*! \brief device flag number, identifies this device */
  static const int kDevMask = 1 << 0;
};
/*! \brief device name GPU */
struct gpu {
  /*! \brief whether this device is CPU or not */
  static const bool kDevCPU = false;
  /*! \brief device flag number, identifies this device */
  static const int kDevMask = 1 << 1;
};