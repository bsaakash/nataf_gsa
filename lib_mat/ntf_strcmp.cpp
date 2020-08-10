//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_strcmp.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 16:42:46
//

// Include Files
#include "ntf_strcmp.h"
#include "ntf_inataf.h"
#include "ntf_inataf_data.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : const coder::array<char, 2U> *a
// Return Type  : boolean_T
//
boolean_T ntf_b_strcmp(const coder::array<char, 2U> &a)
{
  boolean_T b_bool;
  static const char b_cv[3] = { 'M', 'O', 'M' };

  b_bool = false;
  if (a.size(1) == 3) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 3) {
        if (a[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
// Return Type  : boolean_T
//
boolean_T ntf_c_strcmp(const coder::array<char, 2U> &a)
{
  boolean_T b_bool;
  static const char b_cv[3] = { 'D', 'A', 'T' };

  b_bool = false;
  if (a.size(1) == 3) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 3) {
        if (a[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
// Return Type  : boolean_T
//
boolean_T ntf_d_strcmp(const coder::array<char, 2U> &a)
{
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 14) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 14) {
        if (a[kstr] != ntf_cv1[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
// Return Type  : boolean_T
//
boolean_T ntf_e_strcmp(const coder::array<char, 2U> &a)
{
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 16) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 16) {
        if (a[kstr] != ntf_cv2[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
// Return Type  : boolean_T
//
boolean_T ntf_f_strcmp(const coder::array<char, 2U> &a)
{
  boolean_T b_bool;
  static const char b_cv[8] = { 'b', 'i', 'n', 'o', 'm', 'i', 'a', 'l' };

  b_bool = false;
  if (a.size(1) == 8) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 8) {
        if (a[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
// Return Type  : boolean_T
//
boolean_T ntf_g_strcmp(const coder::array<char, 2U> &a)
{
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 9) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 9) {
        if (a[kstr] != ntf_cv3[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
// Return Type  : boolean_T
//
boolean_T ntf_h_strcmp(const coder::array<char, 2U> &a)
{
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 16) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 16) {
        if (a[kstr] != ntf_cv4[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
// Return Type  : boolean_T
//
boolean_T ntf_i_strcmp(const coder::array<char, 2U> &a)
{
  boolean_T b_bool;
  static const char b_cv[7] = { 'p', 'o', 'i', 's', 's', 'o', 'n' };

  b_bool = false;
  if (a.size(1) == 7) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 7) {
        if (a[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
// Return Type  : boolean_T
//
boolean_T ntf_j_strcmp(const coder::array<char, 2U> &a)
{
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 11) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 11) {
        if (a[kstr] != ntf_cv5[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
// Return Type  : boolean_T
//
boolean_T ntf_k_strcmp(const coder::array<char, 2U> &a)
{
  boolean_T b_bool;
  static const char b_cv[5] = { 'g', 'a', 'm', 'm', 'a' };

  b_bool = false;
  if (a.size(1) == 5) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 5) {
        if (a[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
// Return Type  : boolean_T
//
boolean_T ntf_l_strcmp(const coder::array<char, 2U> &a)
{
  boolean_T b_bool;
  static const char b_cv[4] = { 'b', 'e', 't', 'a' };

  b_bool = false;
  if (a.size(1) == 4) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 4) {
        if (a[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
// Return Type  : boolean_T
//
boolean_T ntf_m_strcmp(const coder::array<char, 2U> &a)
{
  boolean_T b_bool;
  static const char b_cv[6] = { 'g', 'u', 'm', 'b', 'e', 'l' };

  b_bool = false;
  if (a.size(1) == 6) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 6) {
        if (a[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
// Return Type  : boolean_T
//
boolean_T ntf_n_strcmp(const coder::array<char, 2U> &a)
{
  boolean_T b_bool;
  static const char b_cv[7] = { 'w', 'e', 'i', 'b', 'u', 'l', 'l' };

  b_bool = false;
  if (a.size(1) == 7) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 7) {
        if (a[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
// Return Type  : boolean_T
//
boolean_T ntf_o_strcmp(const coder::array<char, 2U> &a)
{
  boolean_T b_bool;
  static const char b_cv[3] = { 'g', 'e', 'v' };

  b_bool = false;
  if (a.size(1) == 3) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 3) {
        if (a[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
// Return Type  : boolean_T
//
boolean_T ntf_p_strcmp(const coder::array<char, 2U> &a)
{
  boolean_T b_bool;
  static const char b_cv[8] = { 'r', 'a', 'y', 'l', 'e', 'i', 'g', 'h' };

  b_bool = false;
  if (a.size(1) == 8) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 8) {
        if (a[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
// Return Type  : boolean_T
//
boolean_T ntf_q_strcmp(const coder::array<char, 2U> &a)
{
  boolean_T b_bool;
  static const char b_cv[9] = { 'c', 'h', 'i', 's', 'q', 'u', 'a', 'r', 'e' };

  b_bool = false;
  if (a.size(1) == 9) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 9) {
        if (a[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
// Return Type  : boolean_T
//
boolean_T ntf_r_strcmp(const coder::array<char, 2U> &a)
{
  boolean_T b_bool;
  static const char b_cv[7] = { 'u', 'n', 'i', 'f', 'o', 'r', 'm' };

  b_bool = false;
  if (a.size(1) == 7) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 7) {
        if (a[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
//                const char b[14]
// Return Type  : boolean_T
//
boolean_T ntf_s_strcmp(const coder::array<char, 2U> &a, const char b[14])
{
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 14) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 14) {
        if (a[kstr] != b[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
// Return Type  : boolean_T
//
boolean_T ntf_strcmp(const coder::array<char, 2U> &a)
{
  boolean_T b_bool;
  static const char b_cv[3] = { 'P', 'A', 'R' };

  b_bool = false;
  if (a.size(1) == 3) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 3) {
        if (a[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
//                const char b[16]
// Return Type  : boolean_T
//
boolean_T ntf_t_strcmp(const coder::array<char, 2U> &a, const char b[16])
{
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 16) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 16) {
        if (a[kstr] != b[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
//                const char b[6]
// Return Type  : boolean_T
//
boolean_T ntf_u_strcmp(const coder::array<char, 2U> &a, const char b[6])
{
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 6) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 6) {
        if (a[kstr] != b[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
//                const char b[8]
// Return Type  : boolean_T
//
boolean_T ntf_v_strcmp(const coder::array<char, 2U> &a, const char b[8])
{
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 8) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 8) {
        if (a[kstr] != b[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
// Return Type  : boolean_T
//
boolean_T ntf_w_strcmp(const coder::array<char, 2U> &a)
{
  boolean_T b_bool;
  b_bool = false;
  if (a.size(1) == 9) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 9) {
        if (a[kstr] != ntf_cv6[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
// Return Type  : boolean_T
//
boolean_T ntf_x_strcmp(const coder::array<char, 2U> &a)
{
  boolean_T b_bool;
  static const char b_cv[20] = { 't', 'r', 'u', 'n', 'c', 'a', 't', 'e', 'd',
    'e', 'x', 'p', 'o', 'n', 'e', 'n', 't', 'i', 'a', 'l' };

  b_bool = false;
  if (a.size(1) == 20) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 20) {
        if (a[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// Arguments    : const coder::array<char, 2U> *a
// Return Type  : boolean_T
//
boolean_T ntf_y_strcmp(const coder::array<char, 2U> &a)
{
  boolean_T b_bool;
  static const char b_cv[8] = { 'd', 'i', 's', 'c', 'r', 'e', 't', 'e' };

  b_bool = false;
  if (a.size(1) == 8) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr < 8) {
        if (a[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return b_bool;
}

//
// File trailer for ntf_strcmp.cpp
//
// [EOF]
//
