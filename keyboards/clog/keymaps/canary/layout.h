#ifndef EA502B6B_E3B9_4420_8649_D61A64E84ED8
#define EA502B6B_E3B9_4420_8649_D61A64E84ED8

#include QMK_KEYBOARD_H

// clang-format off

#define LAYOUT_clog(                                       \
          l32, l33, l34, l35,                              \
l20, l21, l22, l23, l24, l25,                              \
     l11, l12, l13, l14, l15,                              \
                                                           \
                    l04, l05,                              \
                                                           \
r35, r34, r33, r32,                                        \
r25, r24, r23, r22, r21, r20,                              \
r15, r14, r13, r12, r11,                                   \
                                                           \
r05, r04                                                   \
) = LAYOUT_split_3x5_2(                                    \
     l20, l32, l33, l34, l35,   r35, r34, r33, r32, r20,   \
     l21, l22, l23, l24, l25,   r25, r24, r23, r22, r21,   \
     l11, l12, l13, l14, l15,   r15, r14, r13, r12, r11,   \
                                                           \
                    l04, l05,   r05, r04                   \
);

// clang-format on

#endif /* EA502B6B_E3B9_4420_8649_D61A64E84ED8 */
