/* Copyright (c) 2018, 2019 Evan Nemerson <evan@nemerson.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "../x86-internal.h"
#include "../../../simde/x86/avx2.h"

#include <stdio.h>

static MunitResult
test_simde_mm256_add_epi8(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m256i a;
    simde__m256i b;
    simde__m256i r;
  } test_vec[8] = {
    { simde_mm256_set_epi8(INT8_C(  38), INT8_C(   7), INT8_C(  -2), INT8_C(  58),
                           INT8_C( 110), INT8_C( -99), INT8_C( -44), INT8_C(  54),
                           INT8_C(  -7), INT8_C(  11), INT8_C(  37), INT8_C(  89),
                           INT8_C(-116), INT8_C( -61), INT8_C( -62), INT8_C(-100),
                           INT8_C(  93), INT8_C(-106), INT8_C( -93), INT8_C( -65),
                           INT8_C(  41), INT8_C(  48), INT8_C( 119), INT8_C( -81),
                           INT8_C( 111), INT8_C(-127), INT8_C( -20), INT8_C(  49),
                           INT8_C( -86), INT8_C(  40), INT8_C(   8), INT8_C( -11)),
      simde_mm256_set_epi8(INT8_C(  39), INT8_C(  75), INT8_C(  21), INT8_C( -79),
                           INT8_C(  76), INT8_C( -46), INT8_C(  91), INT8_C(  40),
                           INT8_C(  97), INT8_C( -98), INT8_C( -82), INT8_C(  44),
                           INT8_C( -73), INT8_C( -89), INT8_C(-127), INT8_C( -32),
                           INT8_C( 120), INT8_C( 113), INT8_C( -53), INT8_C( -49),
                           INT8_C( -63), INT8_C(  81), INT8_C( -64), INT8_C(  90),
                           INT8_C( 100), INT8_C( -73), INT8_C( -51), INT8_C(-117),
                           INT8_C( -40), INT8_C(  69), INT8_C(-110), INT8_C( -48)),
      simde_mm256_set_epi8(INT8_C(  77), INT8_C(  82), INT8_C(  19), INT8_C( -21),
                           INT8_C( -70), INT8_C( 111), INT8_C(  47), INT8_C(  94),
                           INT8_C(  90), INT8_C( -87), INT8_C( -45), INT8_C(-123),
                           INT8_C(  67), INT8_C( 106), INT8_C(  67), INT8_C( 124),
                           INT8_C( -43), INT8_C(   7), INT8_C( 110), INT8_C(-114),
                           INT8_C( -22), INT8_C(-127), INT8_C(  55), INT8_C(   9),
                           INT8_C( -45), INT8_C(  56), INT8_C( -71), INT8_C( -68),
                           INT8_C(-126), INT8_C( 109), INT8_C(-102), INT8_C( -59)) },
    { simde_mm256_set_epi8(INT8_C(  71), INT8_C(   4), INT8_C(  70), INT8_C( -16),
                           INT8_C( -60), INT8_C( -69), INT8_C( -49), INT8_C( 108),
                           INT8_C( 108), INT8_C(  12), INT8_C(  69), INT8_C( -44),
                           INT8_C( 104), INT8_C(-122), INT8_C(  94), INT8_C( -44),
                           INT8_C(  20), INT8_C( -27), INT8_C(  55), INT8_C( 116),
                           INT8_C( 117), INT8_C(-108), INT8_C(  62), INT8_C(-118),
                           INT8_C(  86), INT8_C( -59), INT8_C(   3), INT8_C(  -3),
                           INT8_C( -82), INT8_C( 110), INT8_C(  88), INT8_C(  57)),
      simde_mm256_set_epi8(INT8_C( -80), INT8_C( 112), INT8_C(  78), INT8_C( -63),
                           INT8_C( 105), INT8_C(  59), INT8_C(  13), INT8_C( -94),
                           INT8_C( 116), INT8_C( -39), INT8_C(  42), INT8_C(  69),
                           INT8_C( 119), INT8_C(  -2), INT8_C( -96), INT8_C( -26),
                           INT8_C(  78), INT8_C(  -3), INT8_C( 125), INT8_C(  93),
                           INT8_C( -99), INT8_C( -92), INT8_C(  87), INT8_C( 115),
                           INT8_C( -58), INT8_C( 102), INT8_C(  77), INT8_C(  14),
                           INT8_C(-124), INT8_C(  69), INT8_C( 123), INT8_C(  22)),
      simde_mm256_set_epi8(INT8_C(  -9), INT8_C( 116), INT8_C(-108), INT8_C( -79),
                           INT8_C(  45), INT8_C( -10), INT8_C( -36), INT8_C(  14),
                           INT8_C( -32), INT8_C( -27), INT8_C( 111), INT8_C(  25),
                           INT8_C( -33), INT8_C(-124), INT8_C(  -2), INT8_C( -70),
                           INT8_C(  98), INT8_C( -30), INT8_C( -76), INT8_C( -47),
                           INT8_C(  18), INT8_C(  56), INT8_C(-107), INT8_C(  -3),
                           INT8_C(  28), INT8_C(  43), INT8_C(  80), INT8_C(  11),
                           INT8_C(  50), INT8_C( -77), INT8_C( -45), INT8_C(  79)) },
    { simde_mm256_set_epi8(INT8_C(  35), INT8_C(  50), INT8_C(-118), INT8_C( -51),
                           INT8_C( 104), INT8_C(  20), INT8_C( -38), INT8_C(-105),
                           INT8_C(  57), INT8_C(  19), INT8_C( -89), INT8_C( -46),
                           INT8_C(  27), INT8_C( -40), INT8_C(  -8), INT8_C( -54),
                           INT8_C(  74), INT8_C(-108), INT8_C( -11), INT8_C(  36),
                           INT8_C(  14), INT8_C(  26), INT8_C( -19), INT8_C( -47),
                           INT8_C(  70), INT8_C( -22), INT8_C(   1), INT8_C(  48),
                           INT8_C(-104), INT8_C(  96), INT8_C(  54), INT8_C( -65)),
      simde_mm256_set_epi8(INT8_C(  28), INT8_C( -52), INT8_C( 107), INT8_C(-103),
                           INT8_C( 110), INT8_C(  86), INT8_C(  60), INT8_C(   2),
                           INT8_C( -17), INT8_C(  30), INT8_C( -28), INT8_C( -92),
                           INT8_C(  93), INT8_C( 112), INT8_C( -31), INT8_C(  -9),
                           INT8_C(   8), INT8_C( -36), INT8_C( -58), INT8_C(-120),
                           INT8_C( -53), INT8_C(  26), INT8_C( -55), INT8_C( -73),
                           INT8_C(  20), INT8_C(  83), INT8_C( 124), INT8_C(  54),
                           INT8_C(  30), INT8_C( -54), INT8_C( -43), INT8_C(-123)),
      simde_mm256_set_epi8(INT8_C(  63), INT8_C(  -2), INT8_C( -11), INT8_C( 102),
                           INT8_C( -42), INT8_C( 106), INT8_C(  22), INT8_C(-103),
                           INT8_C(  40), INT8_C(  49), INT8_C(-117), INT8_C( 118),
                           INT8_C( 120), INT8_C(  72), INT8_C( -39), INT8_C( -63),
                           INT8_C(  82), INT8_C( 112), INT8_C( -69), INT8_C( -84),
                           INT8_C( -39), INT8_C(  52), INT8_C( -74), INT8_C(-120),
                           INT8_C(  90), INT8_C(  61), INT8_C( 125), INT8_C( 102),
                           INT8_C( -74), INT8_C(  42), INT8_C(  11), INT8_C(  68)) },
    { simde_mm256_set_epi8(INT8_C( -39), INT8_C( 114), INT8_C(  -7), INT8_C( 121),
                           INT8_C(  92), INT8_C(  79), INT8_C( 102), INT8_C(  76),
                           INT8_C( 109), INT8_C( -19), INT8_C(  70), INT8_C( -60),
                           INT8_C(  69), INT8_C( -31), INT8_C(  37), INT8_C(  40),
                           INT8_C( -46), INT8_C(  88), INT8_C( -21), INT8_C( -43),
                           INT8_C(  83), INT8_C(  14), INT8_C( -23), INT8_C( -33),
                           INT8_C(  86), INT8_C( -85), INT8_C(   8), INT8_C(  59),
                           INT8_C( 123), INT8_C(  93), INT8_C( -22), INT8_C(  26)),
      simde_mm256_set_epi8(INT8_C( 116), INT8_C( -91), INT8_C(  32), INT8_C( -33),
                           INT8_C(-123), INT8_C(-113), INT8_C(  98), INT8_C( -60),
                           INT8_C(-116), INT8_C( -75), INT8_C(  96), INT8_C(  10),
                           INT8_C( -53), INT8_C( -10), INT8_C( -80), INT8_C(-128),
                           INT8_C(  59), INT8_C( -73), INT8_C( -11), INT8_C(   8),
                           INT8_C(-127), INT8_C(-108), INT8_C(-124), INT8_C( 111),
                           INT8_C( -79), INT8_C(  28), INT8_C(  24), INT8_C(  40),
                           INT8_C(  40), INT8_C(  29), INT8_C( 119), INT8_C( 100)),
      simde_mm256_set_epi8(INT8_C(  77), INT8_C(  23), INT8_C(  25), INT8_C(  88),
                           INT8_C( -31), INT8_C( -34), INT8_C( -56), INT8_C(  16),
                           INT8_C(  -7), INT8_C( -94), INT8_C( -90), INT8_C( -50),
                           INT8_C(  16), INT8_C( -41), INT8_C( -43), INT8_C( -88),
                           INT8_C(  13), INT8_C(  15), INT8_C( -32), INT8_C( -35),
                           INT8_C( -44), INT8_C( -94), INT8_C( 109), INT8_C(  78),
                           INT8_C(   7), INT8_C( -57), INT8_C(  32), INT8_C(  99),
                           INT8_C( -93), INT8_C( 122), INT8_C(  97), INT8_C( 126)) },
    { simde_mm256_set_epi8(INT8_C(-108), INT8_C( -39), INT8_C( -41), INT8_C( 120),
                           INT8_C(-106), INT8_C( -66), INT8_C( -98), INT8_C( -12),
                           INT8_C(-106), INT8_C( -94), INT8_C( -31), INT8_C( -14),
                           INT8_C(  -2), INT8_C( -34), INT8_C( -30), INT8_C( -64),
                           INT8_C(  65), INT8_C(  50), INT8_C(  73), INT8_C( -32),
                           INT8_C( 106), INT8_C(-126), INT8_C(  67), INT8_C(  53),
                           INT8_C( 104), INT8_C(  17), INT8_C( -36), INT8_C(  95),
                           INT8_C(  57), INT8_C(  32), INT8_C( -59), INT8_C( -12)),
      simde_mm256_set_epi8(INT8_C(  29), INT8_C(  61), INT8_C( -31), INT8_C( 122),
                           INT8_C(   8), INT8_C( -70), INT8_C(  11), INT8_C(  62),
                           INT8_C( -73), INT8_C( -96), INT8_C( -10), INT8_C( -40),
                           INT8_C( -52), INT8_C( -38), INT8_C(  92), INT8_C(  51),
                           INT8_C(  35), INT8_C(  53), INT8_C(  88), INT8_C( -11),
                           INT8_C(  57), INT8_C(-113), INT8_C(-123), INT8_C( 106),
                           INT8_C(-110), INT8_C(-110), INT8_C(   2), INT8_C(  67),
                           INT8_C( -30), INT8_C( -96), INT8_C( -97), INT8_C( -86)),
      simde_mm256_set_epi8(INT8_C( -79), INT8_C(  22), INT8_C( -72), INT8_C( -14),
                           INT8_C( -98), INT8_C( 120), INT8_C( -87), INT8_C(  50),
                           INT8_C(  77), INT8_C(  66), INT8_C( -41), INT8_C( -54),
                           INT8_C( -54), INT8_C( -72), INT8_C(  62), INT8_C( -13),
                           INT8_C( 100), INT8_C( 103), INT8_C( -95), INT8_C( -43),
                           INT8_C( -93), INT8_C(  17), INT8_C( -56), INT8_C( -97),
                           INT8_C(  -6), INT8_C( -93), INT8_C( -34), INT8_C( -94),
                           INT8_C(  27), INT8_C( -64), INT8_C( 100), INT8_C( -98)) },
    { simde_mm256_set_epi8(INT8_C( -25), INT8_C( -91), INT8_C(  57), INT8_C( -61),
                           INT8_C(  27), INT8_C( -92), INT8_C(-114), INT8_C(-104),
                           INT8_C( 125), INT8_C( 120), INT8_C( -30), INT8_C(   8),
                           INT8_C(  88), INT8_C( -75), INT8_C( 100), INT8_C(  97),
                           INT8_C( -61), INT8_C( 122), INT8_C(  27), INT8_C( -70),
                           INT8_C( -30), INT8_C( -60), INT8_C( -90), INT8_C( -43),
                           INT8_C( -10), INT8_C( -38), INT8_C(  12), INT8_C(  90),
                           INT8_C(   1), INT8_C(  39), INT8_C( -80), INT8_C(  53)),
      simde_mm256_set_epi8(INT8_C( 121), INT8_C(  85), INT8_C(-111), INT8_C(-111),
                           INT8_C(  84), INT8_C(  54), INT8_C( -52), INT8_C( -62),
                           INT8_C( -55), INT8_C(  17), INT8_C(  68), INT8_C(  63),
                           INT8_C( 113), INT8_C( -67), INT8_C( -38), INT8_C(-118),
                           INT8_C(-104), INT8_C( -71), INT8_C(  55), INT8_C(  21),
                           INT8_C( -66), INT8_C(  19), INT8_C(-123), INT8_C(  95),
                           INT8_C( 118), INT8_C(  65), INT8_C( -70), INT8_C( -13),
                           INT8_C( 120), INT8_C( -27), INT8_C( -66), INT8_C( 122)),
      simde_mm256_set_epi8(INT8_C(  96), INT8_C(  -6), INT8_C( -54), INT8_C(  84),
                           INT8_C( 111), INT8_C( -38), INT8_C(  90), INT8_C(  90),
                           INT8_C(  70), INT8_C(-119), INT8_C(  38), INT8_C(  71),
                           INT8_C( -55), INT8_C( 114), INT8_C(  62), INT8_C( -21),
                           INT8_C(  91), INT8_C(  51), INT8_C(  82), INT8_C( -49),
                           INT8_C( -96), INT8_C( -41), INT8_C(  43), INT8_C(  52),
                           INT8_C( 108), INT8_C(  27), INT8_C( -58), INT8_C(  77),
                           INT8_C( 121), INT8_C(  12), INT8_C( 110), INT8_C( -81)) },
    { simde_mm256_set_epi8(INT8_C( 117), INT8_C( -64), INT8_C(  32), INT8_C( -52),
                           INT8_C(  16), INT8_C( -33), INT8_C(  14), INT8_C( -85),
                           INT8_C(   3), INT8_C( -57), INT8_C( -94), INT8_C( -41),
                           INT8_C( -98), INT8_C( 127), INT8_C(  42), INT8_C(  48),
                           INT8_C(  17), INT8_C( 106), INT8_C( -29), INT8_C( -56),
                           INT8_C(  75), INT8_C(-117), INT8_C( 106), INT8_C(  46),
                           INT8_C(-110), INT8_C( 123), INT8_C(  46), INT8_C(   8),
                           INT8_C(-118), INT8_C( 103), INT8_C(  19), INT8_C(  26)),
      simde_mm256_set_epi8(INT8_C(-123), INT8_C(  76), INT8_C( 117), INT8_C(  39),
                           INT8_C( 120), INT8_C( -11), INT8_C(  12), INT8_C( -12),
                           INT8_C( -32), INT8_C(   7), INT8_C(  13), INT8_C(  45),
                           INT8_C(  60), INT8_C( -83), INT8_C( -84), INT8_C( -17),
                           INT8_C( -88), INT8_C( -57), INT8_C( 102), INT8_C( -44),
                           INT8_C( 119), INT8_C(  16), INT8_C( 101), INT8_C( -86),
                           INT8_C(-106), INT8_C(-124), INT8_C(  83), INT8_C(-127),
                           INT8_C(  55), INT8_C( -92), INT8_C(  15), INT8_C(-114)),
      simde_mm256_set_epi8(INT8_C(  -6), INT8_C(  12), INT8_C(-107), INT8_C( -13),
                           INT8_C(-120), INT8_C( -44), INT8_C(  26), INT8_C( -97),
                           INT8_C( -29), INT8_C( -50), INT8_C( -81), INT8_C(   4),
                           INT8_C( -38), INT8_C(  44), INT8_C( -42), INT8_C(  31),
                           INT8_C( -71), INT8_C(  49), INT8_C(  73), INT8_C(-100),
                           INT8_C( -62), INT8_C(-101), INT8_C( -49), INT8_C( -40),
                           INT8_C(  40), INT8_C(  -1), INT8_C(-127), INT8_C(-119),
                           INT8_C( -63), INT8_C(  11), INT8_C(  34), INT8_C( -88)) },
    { simde_mm256_set_epi8(INT8_C(-111), INT8_C( -68), INT8_C( -72), INT8_C(-123),
                           INT8_C(  60), INT8_C(  19), INT8_C( -56), INT8_C( -34),
                           INT8_C(  75), INT8_C(-101), INT8_C(  82), INT8_C(  25),
                           INT8_C( 119), INT8_C(  87), INT8_C(  12), INT8_C( -81),
                           INT8_C( 120), INT8_C(  58), INT8_C(  77), INT8_C(-102),
                           INT8_C( -65), INT8_C(  14), INT8_C(  32), INT8_C(-111),
                           INT8_C(  72), INT8_C(  -1), INT8_C( 117), INT8_C(-104),
                           INT8_C(  81), INT8_C( -80), INT8_C( -43), INT8_C( -80)),
      simde_mm256_set_epi8(INT8_C( 114), INT8_C( -63), INT8_C(  59), INT8_C( -32),
                           INT8_C( 113), INT8_C(-103), INT8_C( -89), INT8_C( -53),
                           INT8_C( -11), INT8_C(  31), INT8_C(  71), INT8_C( -59),
                           INT8_C(  89), INT8_C(  28), INT8_C(  76), INT8_C(  62),
                           INT8_C(  13), INT8_C( 105), INT8_C( -93), INT8_C(  64),
                           INT8_C( -40), INT8_C(  38), INT8_C( -73), INT8_C(-114),
                           INT8_C(-121), INT8_C( -54), INT8_C(-113), INT8_C(   1),
                           INT8_C( -77), INT8_C( -55), INT8_C(  24), INT8_C( -16)),
      simde_mm256_set_epi8(INT8_C(   3), INT8_C( 125), INT8_C( -13), INT8_C( 101),
                           INT8_C( -83), INT8_C( -84), INT8_C( 111), INT8_C( -87),
                           INT8_C(  64), INT8_C( -70), INT8_C(-103), INT8_C( -34),
                           INT8_C( -48), INT8_C( 115), INT8_C(  88), INT8_C( -19),
                           INT8_C(-123), INT8_C( -93), INT8_C( -16), INT8_C( -38),
                           INT8_C(-105), INT8_C(  52), INT8_C( -41), INT8_C(  31),
                           INT8_C( -49), INT8_C( -55), INT8_C(   4), INT8_C(-103),
                           INT8_C(   4), INT8_C( 121), INT8_C( -19), INT8_C( -96)) }
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_add_epi8(test_vec[i].a, test_vec[i].b);
    simde_assert_m256i_i8(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_add_epi16(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m256i a;
    simde__m256i b;
    simde__m256i r;
  } test_vec[8] = {
    { simde_mm256_set_epi16(INT16_C(-12908), INT16_C(-15352), INT16_C( -9871), INT16_C( 11131),
                            INT16_C(-13055), INT16_C( 26967), INT16_C(-23057), INT16_C( 20309),
                            INT16_C(-12549), INT16_C(-20367), INT16_C(  6732), INT16_C( -7853),
                            INT16_C(-23923), INT16_C( -3719), INT16_C(-28976), INT16_C( 10001)),
      simde_mm256_set_epi16(INT16_C( 13883), INT16_C( 24989), INT16_C(-27634), INT16_C( 20264),
                            INT16_C( 15739), INT16_C(-13782), INT16_C( -2125), INT16_C(-14153),
                            INT16_C( -5381), INT16_C(-18938), INT16_C(-15901), INT16_C( -7111),
                            INT16_C(-11138), INT16_C( 23506), INT16_C( -6177), INT16_C(-29557)),
      simde_mm256_set_epi16(INT16_C(   975), INT16_C(  9637), INT16_C( 28031), INT16_C( 31395),
                            INT16_C(  2684), INT16_C( 13185), INT16_C(-25182), INT16_C(  6156),
                            INT16_C(-17930), INT16_C( 26231), INT16_C( -9169), INT16_C(-14964),
                            INT16_C( 30475), INT16_C( 19787), INT16_C( 30383), INT16_C(-19556)) },
    { simde_mm256_set_epi16(INT16_C(-20529), INT16_C(-26039), INT16_C( 27693), INT16_C(-13325),
                            INT16_C(-24443), INT16_C(-32106), INT16_C(-21283), INT16_C( -3709),
                            INT16_C(   747), INT16_C( 18820), INT16_C(-26624), INT16_C( 10967),
                            INT16_C( 25066), INT16_C( 19698), INT16_C(-32202), INT16_C(-11757)),
      simde_mm256_set_epi16(INT16_C( 10244), INT16_C(-18450), INT16_C(  5048), INT16_C( -3511),
                            INT16_C(-16723), INT16_C(-30842), INT16_C( 22572), INT16_C( -8065),
                            INT16_C( 30703), INT16_C(-26965), INT16_C( 23628), INT16_C(-27177),
                            INT16_C(-17808), INT16_C(-15958), INT16_C( 15529), INT16_C( 11766)),
      simde_mm256_set_epi16(INT16_C(-10285), INT16_C( 21047), INT16_C( 32741), INT16_C(-16836),
                            INT16_C( 24370), INT16_C(  2588), INT16_C(  1289), INT16_C(-11774),
                            INT16_C( 31450), INT16_C( -8145), INT16_C( -2996), INT16_C(-16210),
                            INT16_C(  7258), INT16_C(  3740), INT16_C(-16673), INT16_C(     9)) },
    { simde_mm256_set_epi16(INT16_C( 20347), INT16_C( 23946), INT16_C( 24055), INT16_C(  9643),
                            INT16_C( -2110), INT16_C(-31092), INT16_C(-13787), INT16_C( -6302),
                            INT16_C(  1396), INT16_C(  8481), INT16_C(-32148), INT16_C( 29268),
                            INT16_C( -9419), INT16_C( -3935), INT16_C( -1720), INT16_C(-10026)),
      simde_mm256_set_epi16(INT16_C( 15679), INT16_C( -2155), INT16_C( 32033), INT16_C( -2216),
                            INT16_C(-11561), INT16_C( 32737), INT16_C(-28164), INT16_C(  9867),
                            INT16_C( 17610), INT16_C(-22692), INT16_C(-28058), INT16_C(  7040),
                            INT16_C( 26754), INT16_C( -3306), INT16_C( -7351), INT16_C( 27370)),
      simde_mm256_set_epi16(INT16_C(-29510), INT16_C( 21791), INT16_C( -9448), INT16_C(  7427),
                            INT16_C(-13671), INT16_C(  1645), INT16_C( 23585), INT16_C(  3565),
                            INT16_C( 19006), INT16_C(-14211), INT16_C(  5330), INT16_C(-29228),
                            INT16_C( 17335), INT16_C( -7241), INT16_C( -9071), INT16_C( 17344)) },
    { simde_mm256_set_epi16(INT16_C(-27154), INT16_C(-23947), INT16_C(  1952), INT16_C(  7823),
                            INT16_C( 29492), INT16_C( -6766), INT16_C( 11046), INT16_C( 22007),
                            INT16_C( 15625), INT16_C( -6212), INT16_C( 31802), INT16_C( 17826),
                            INT16_C( 14647), INT16_C( 24188), INT16_C(-26765), INT16_C( 18766)),
      simde_mm256_set_epi16(INT16_C(-26373), INT16_C( 11481), INT16_C(-29646), INT16_C(-31758),
                            INT16_C(-13826), INT16_C( 16818), INT16_C( -2585), INT16_C(  3549),
                            INT16_C(   930), INT16_C(-29705), INT16_C(-19505), INT16_C(-18939),
                            INT16_C(-22195), INT16_C(  6794), INT16_C(  4204), INT16_C( 28707)),
      simde_mm256_set_epi16(INT16_C( 12009), INT16_C(-12466), INT16_C(-27694), INT16_C(-23935),
                            INT16_C( 15666), INT16_C( 10052), INT16_C(  8461), INT16_C( 25556),
                            INT16_C( 16555), INT16_C( 29619), INT16_C( 12297), INT16_C( -1113),
                            INT16_C( -7548), INT16_C( 30982), INT16_C(-22561), INT16_C(-18063)) },
    { simde_mm256_set_epi16(INT16_C( 30710), INT16_C( 24751), INT16_C( -4369), INT16_C( 18532),
                            INT16_C( 22682), INT16_C( 30280), INT16_C( 11292), INT16_C( 11710),
                            INT16_C(-17556), INT16_C( 10009), INT16_C(-27333), INT16_C( 22196),
                            INT16_C(-19056), INT16_C( -7837), INT16_C( 29666), INT16_C(  6547)),
      simde_mm256_set_epi16(INT16_C( -2566), INT16_C(  5814), INT16_C( 26818), INT16_C( 27091),
                            INT16_C(-10234), INT16_C( 23509), INT16_C( 13267), INT16_C( -7338),
                            INT16_C( 13949), INT16_C(  1472), INT16_C( 11063), INT16_C( -7215),
                            INT16_C( -8090), INT16_C(-23785), INT16_C(-15335), INT16_C(  4848)),
      simde_mm256_set_epi16(INT16_C( 28144), INT16_C( 30565), INT16_C( 22449), INT16_C(-19913),
                            INT16_C( 12448), INT16_C(-11747), INT16_C( 24559), INT16_C(  4372),
                            INT16_C( -3607), INT16_C( 11481), INT16_C(-16270), INT16_C( 14981),
                            INT16_C(-27146), INT16_C(-31622), INT16_C( 14331), INT16_C( 11395)) },
    { simde_mm256_set_epi16(INT16_C( 30207), INT16_C(-18325), INT16_C(  1180), INT16_C(-26389),
                            INT16_C( 14745), INT16_C(  7441), INT16_C(-23138), INT16_C(-20960),
                            INT16_C( 16686), INT16_C(-12834), INT16_C( -5724), INT16_C(  1237),
                            INT16_C( 12783), INT16_C( -1549), INT16_C(  7604), INT16_C(-25399)),
      simde_mm256_set_epi16(INT16_C( -5331), INT16_C(-23526), INT16_C( 14670), INT16_C(-15592),
                            INT16_C( 18159), INT16_C(  4760), INT16_C( 10369), INT16_C(-25724),
                            INT16_C(-28583), INT16_C( -6941), INT16_C(-17844), INT16_C(-14094),
                            INT16_C( 16769), INT16_C( 12540), INT16_C(-26071), INT16_C(  8463)),
      simde_mm256_set_epi16(INT16_C( 24876), INT16_C( 23685), INT16_C( 15850), INT16_C( 23555),
                            INT16_C(-32632), INT16_C( 12201), INT16_C(-12769), INT16_C( 18852),
                            INT16_C(-11897), INT16_C(-19775), INT16_C(-23568), INT16_C(-12857),
                            INT16_C( 29552), INT16_C( 10991), INT16_C(-18467), INT16_C(-16936)) },
    { simde_mm256_set_epi16(INT16_C( 28357), INT16_C( 20172), INT16_C( 17421), INT16_C(-11866),
                            INT16_C(-11434), INT16_C( 24363), INT16_C( 30807), INT16_C( -1507),
                            INT16_C(-31442), INT16_C( 25409), INT16_C( 25186), INT16_C( 22807),
                            INT16_C(-13333), INT16_C(-32257), INT16_C(-15570), INT16_C(  2752)),
      simde_mm256_set_epi16(INT16_C(-19799), INT16_C(-19809), INT16_C(-16948), INT16_C( -1715),
                            INT16_C( 29345), INT16_C(-32027), INT16_C(  5007), INT16_C(  4903),
                            INT16_C( -2392), INT16_C(-30038), INT16_C( 23207), INT16_C(-24060),
                            INT16_C( 29275), INT16_C( 13317), INT16_C( 26431), INT16_C( 23940)),
      simde_mm256_set_epi16(INT16_C(  8558), INT16_C(   363), INT16_C(   473), INT16_C(-13581),
                            INT16_C( 17911), INT16_C( -7664), INT16_C(-29722), INT16_C(  3396),
                            INT16_C( 31702), INT16_C( -4629), INT16_C(-17143), INT16_C( -1253),
                            INT16_C( 15942), INT16_C(-18940), INT16_C( 10861), INT16_C( 26692)) },
    { simde_mm256_set_epi16(INT16_C(  6003), INT16_C( 21193), INT16_C( 27446), INT16_C( 12164),
                            INT16_C(-15839), INT16_C(-27621), INT16_C( 27366), INT16_C(  3166),
                            INT16_C(-14586), INT16_C( 16192), INT16_C( 17380), INT16_C(  2397),
                            INT16_C( 17243), INT16_C(  7969), INT16_C(-18393), INT16_C(-28306)),
      simde_mm256_set_epi16(INT16_C( -9798), INT16_C(  1801), INT16_C(-11340), INT16_C(-25270),
                            INT16_C( -7120), INT16_C( -2660), INT16_C( 23941), INT16_C( 18110),
                            INT16_C( -3348), INT16_C( -5762), INT16_C( 30271), INT16_C(  3473),
                            INT16_C( -7979), INT16_C( -3070), INT16_C( 12208), INT16_C( 30362)),
      simde_mm256_set_epi16(INT16_C( -3795), INT16_C( 22994), INT16_C( 16106), INT16_C(-13106),
                            INT16_C(-22959), INT16_C(-30281), INT16_C(-14229), INT16_C( 21276),
                            INT16_C(-17934), INT16_C( 10430), INT16_C(-17885), INT16_C(  5870),
                            INT16_C(  9264), INT16_C(  4899), INT16_C( -6185), INT16_C(  2056)) }
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_add_epi16(test_vec[i].a, test_vec[i].b);
    simde_assert_m256i_i16(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_add_epi32(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m256i a;
    simde__m256i b;
    simde__m256i r;
  } test_vec[8] = {
    { simde_mm256_set_epi32(INT32_C( 1102687755), INT32_C( 1275949869), INT32_C( -388043296), INT32_C( 1616523445),
                            INT32_C( -312991452), INT32_C(-1980926618), INT32_C( 1274012126), INT32_C(  -45808693)),
      simde_mm256_set_epi32(INT32_C(-1821401638), INT32_C( 1143218625), INT32_C(-1072188421), INT32_C( -228883992),
                            INT32_C( 1453787917), INT32_C(-1686415046), INT32_C(-1856178723), INT32_C(-1344248495)),
      simde_mm256_set_epi32(INT32_C( -718713883), INT32_C(-1875798802), INT32_C(-1460231717), INT32_C( 1387639453),
                            INT32_C( 1140796465), INT32_C(  627625632), INT32_C( -582166597), INT32_C(-1390057188)) },
    { simde_mm256_set_epi32(INT32_C( -511556352), INT32_C(  512138684), INT32_C( 2115720361), INT32_C( -345092241),
                            INT32_C( -115713034), INT32_C( 1435785542), INT32_C( -578341737), INT32_C(  626663856)),
      simde_mm256_set_epi32(INT32_C( 1905028737), INT32_C(  164639990), INT32_C(-1952346601), INT32_C( 1853095591),
                            INT32_C(-1825217200), INT32_C(-1102744367), INT32_C(-1105586227), INT32_C(-1908622941)),
      simde_mm256_set_epi32(INT32_C( 1393472385), INT32_C(  676778674), INT32_C(  163373760), INT32_C( 1508003350),
                            INT32_C(-1940930234), INT32_C(  333041175), INT32_C(-1683927964), INT32_C(-1281959085)) },
    { simde_mm256_set_epi32(INT32_C(  841608097), INT32_C(-2001797484), INT32_C(-1658305288), INT32_C(  966942303),
                            INT32_C(  842108123), INT32_C(  697774066), INT32_C(-1273233002), INT32_C( -331057125)),
      simde_mm256_set_epi32(INT32_C(  824745259), INT32_C( 1162513122), INT32_C( 1536105364), INT32_C( 1572988069),
                            INT32_C( 1601630355), INT32_C(  105174023), INT32_C( -548723565), INT32_C(  342919548)),
      simde_mm256_set_epi32(INT32_C( 1666353356), INT32_C( -839284362), INT32_C( -122199924), INT32_C(-1755036924),
                            INT32_C(-1851228818), INT32_C(  802948089), INT32_C(-1821956567), INT32_C(   11862423)) },
    { simde_mm256_set_epi32(INT32_C(-1982661498), INT32_C( -454967885), INT32_C( 1606399367), INT32_C( 1911771725),
                            INT32_C( -320200723), INT32_C( 2055189331), INT32_C( 1782567162), INT32_C(  617047003)),
      simde_mm256_set_epi32(INT32_C(-1988185598), INT32_C( 1350171177), INT32_C( -741176174), INT32_C( 1024642864),
                            INT32_C( 1174775607), INT32_C(-1489493977), INT32_C( 2114610376), INT32_C(-1150946108)),
      simde_mm256_set_epi32(INT32_C(  324120200), INT32_C(  895203292), INT32_C(  865223193), INT32_C(-1358552707),
                            INT32_C(  854574884), INT32_C(  565695354), INT32_C( -397789758), INT32_C( -533899105)) },
    { simde_mm256_set_epi32(INT32_C(-1636237507), INT32_C(-2022044523), INT32_C( 1298417038), INT32_C( -498789244),
                            INT32_C(-1120565370), INT32_C(  -10552717), INT32_C( 1267811859), INT32_C( 1736112342)),
      simde_mm256_set_epi32(INT32_C(   30746202), INT32_C( 1464439343), INT32_C( 1694184093), INT32_C(-1066802952),
                            INT32_C( -664495133), INT32_C(-2016253412), INT32_C(-1975304715), INT32_C(  -70672826)),
      simde_mm256_set_epi32(INT32_C(-1605491305), INT32_C( -557605180), INT32_C(-1302366165), INT32_C(-1565592196),
                            INT32_C(-1785060503), INT32_C(-2026806129), INT32_C( -707492856), INT32_C( 1665439516)) },
    { simde_mm256_set_epi32(INT32_C(  289000373), INT32_C( 1573632519), INT32_C(  -39248751), INT32_C( -989305129),
                            INT32_C( -946333511), INT32_C( -275686449), INT32_C(  -98660627), INT32_C(-1519479102)),
      simde_mm256_set_epi32(INT32_C(  297476793), INT32_C(  436731799), INT32_C(  124294563), INT32_C(-1635813332),
                            INT32_C(  263383074), INT32_C( -533172755), INT32_C( 1125990821), INT32_C( -786980387)),
      simde_mm256_set_epi32(INT32_C(  586477166), INT32_C( 2010364318), INT32_C(   85045812), INT32_C( 1669848835),
                            INT32_C( -682950437), INT32_C( -808859204), INT32_C( 1027330194), INT32_C( 1988507807)) },
    { simde_mm256_set_epi32(INT32_C(  518182194), INT32_C(-1204047142), INT32_C(  -66070725), INT32_C(  499109808),
                            INT32_C(-2041576579), INT32_C( -621515360), INT32_C(  566201077), INT32_C(  301667364)),
      simde_mm256_set_epi32(INT32_C(-1846226401), INT32_C(-1479610627), INT32_C( -205605694), INT32_C( 2074175879),
                            INT32_C(  797873427), INT32_C(  232260429), INT32_C( 2122451120), INT32_C(-1502060759)),
      simde_mm256_set_epi32(INT32_C(-1328044207), INT32_C( 1611309527), INT32_C( -271676419), INT32_C(-1721681609),
                            INT32_C(-1243703152), INT32_C( -389254931), INT32_C(-1606315099), INT32_C(-1200393395)) },
    { simde_mm256_set_epi32(INT32_C(  405834501), INT32_C(-1910761465), INT32_C(  957239954), INT32_C( -786856288),
                            INT32_C(  843920617), INT32_C(  327146567), INT32_C( -333483012), INT32_C(-1269489720)),
      simde_mm256_set_epi32(INT32_C( -343554450), INT32_C( -768698719), INT32_C(-1629325598), INT32_C(  -86112156),
                            INT32_C(-1762054840), INT32_C(-1230219631), INT32_C(-1955142376), INT32_C(  681367456)),
      simde_mm256_set_epi32(INT32_C(   62280051), INT32_C( 1615507112), INT32_C( -672085644), INT32_C( -872968444),
                            INT32_C( -918134223), INT32_C( -903073064), INT32_C( 2006341908), INT32_C( -588122264)) }
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_add_epi32(test_vec[i].a, test_vec[i].b);
    simde_assert_m256i_i32(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_add_epi64(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m256i a;
    simde__m256i b;
    simde__m256i r;
  } test_vec[8] = {
    { simde_mm256_set_epi64x(INT64_C( -919395005897301486), INT64_C( -150854599157471417),
                             INT64_C( 8808382520295569970), INT64_C(-2573562509116397532)),
      simde_mm256_set_epi64x(INT64_C( 3276842246935198107), INT64_C(  509596195322373870),
                             INT64_C( 5497236691336464382), INT64_C( 7792219835689675301)),
      simde_mm256_set_epi64x(INT64_C( 2357447241037896621), INT64_C(  358741596164902453),
                             INT64_C(-4141124862077517264), INT64_C( 5218657326573277769)) },
    { simde_mm256_set_epi64x(INT64_C(-8319032728400165160), INT64_C( 5761166475766138642),
                             INT64_C( 1889840457419449714), INT64_C(-7866468136110945528)),
      simde_mm256_set_epi64x(INT64_C(-7943707797090752726), INT64_C(-3031420544278169311),
                             INT64_C( -274806827926037798), INT64_C(-6305854756278616306)),
      simde_mm256_set_epi64x(INT64_C( 2184003548218633730), INT64_C( 2729745931487969331),
                             INT64_C( 1615033629493411916), INT64_C( 4274421181319989782)) },
    { simde_mm256_set_epi64x(INT64_C( 5895960517559859999), INT64_C( 6208968053276251170),
                             INT64_C( 7761614749466428803), INT64_C(-6998556565488043930)),
      simde_mm256_set_epi64x(INT64_C(-7645095141522766353), INT64_C( 7326575676453958933),
                             INT64_C( 1354311398343021783), INT64_C( 5074528974494991107)),
      simde_mm256_set_epi64x(INT64_C(-1749134623962906354), INT64_C(-4911200343979341513),
                             INT64_C( 9115926147809450586), INT64_C(-1924027590993052823)) },
    { simde_mm256_set_epi64x(INT64_C( 7265152682832433510), INT64_C(-3085894531646767861),
                             INT64_C(-9131129251692740054), INT64_C(  -13949299420174832)),
      simde_mm256_set_epi64x(INT64_C(-8945299951793325147), INT64_C( 1105999600596947619),
                             INT64_C( 1005965954309535795), INT64_C( 6577596548744990052)),
      simde_mm256_set_epi64x(INT64_C(-1680147268960891637), INT64_C(-1979894931049820242),
                             INT64_C(-8125163297383204259), INT64_C( 6563647249324815220)) },
    { simde_mm256_set_epi64x(INT64_C(-1757821625677084255), INT64_C(-2404608367637526264),
                             INT64_C(  707296317246937957), INT64_C(-8620111396460581683)),
      simde_mm256_set_epi64x(INT64_C(-3596883371125205809), INT64_C( 2676371285603083419),
                             INT64_C( 6821095199901887872), INT64_C(-7512247745220049837)),
      simde_mm256_set_epi64x(INT64_C(-5354704996802290064), INT64_C(  271762917965557155),
                             INT64_C( 7528391517148825829), INT64_C( 2314384932028920096)) },
    { simde_mm256_set_epi64x(INT64_C( 6839811261830973327), INT64_C( 5631394124827236824),
                             INT64_C(-5955019407573777834), INT64_C(-3458836099791348328)),
      simde_mm256_set_epi64x(INT64_C( 7744082525445212477), INT64_C(-8800502010596219205),
                             INT64_C(  384951712332227405), INT64_C(  430518285591300198)),
      simde_mm256_set_epi64x(INT64_C(-3862850286433365812), INT64_C(-3169107885768982381),
                             INT64_C(-5570067695241550429), INT64_C(-3028317814200048130)) },
    { simde_mm256_set_epi64x(INT64_C(-3472881623031498101), INT64_C(-1430648476837955016),
                             INT64_C(-3715397159055217239), INT64_C( 5273106926976979674)),
      simde_mm256_set_epi64x(INT64_C(-4550310691059172162), INT64_C( 3088580064706171589),
                             INT64_C( 5815698628016314327), INT64_C(-8735000016575196569)),
      simde_mm256_set_epi64x(INT64_C(-8023192314090670263), INT64_C( 1657931587868216573),
                             INT64_C( 2100301468961097088), INT64_C(-3461893089598216895)) },
    { simde_mm256_set_epi64x(INT64_C(-8609934348254886079), INT64_C( 4626495260054383935),
                             INT64_C(-1742895605763712389), INT64_C( 8190624861564512538)),
      simde_mm256_set_epi64x(INT64_C(-1653872282243675761), INT64_C(-8277823144431279152),
                             INT64_C( 5269960775097450688), INT64_C( 3526432474948394359)),
      simde_mm256_set_epi64x(INT64_C( 8182937443210989776), INT64_C(-3651327884376895217),
                             INT64_C( 3527065169333738299), INT64_C(-6729686737196644719)) }
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_add_epi64(test_vec[i].a, test_vec[i].b);
    simde_assert_m256i_i64(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_and_si256(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m256i a;
    simde__m256i b;
    simde__m256i r;
  } test_vec[8] = {
    { simde_mm256_set_epi64x(INT64_C( 8722470578646828517), INT64_C(  891261850847437783),
                             INT64_C( 8698554819020653857), INT64_C(-7282900013878242954)),
      simde_mm256_set_epi64x(INT64_C(-8128142018056442141), INT64_C( 5559182722028422309),
                             INT64_C( 2093267872519066825), INT64_C(-7117023562774970023)),
      simde_mm256_set_epi64x(INT64_C(  648519197013312737), INT64_C(  866420841735143557),
                             INT64_C( 1730587322060899329), INT64_C(-7482378910948097712)) },
    { simde_mm256_set_epi64x(INT64_C(-2297219683620407228), INT64_C(-2314825045857877411),
                             INT64_C(-2223407797787304327), INT64_C( 5408595704702705619)),
      simde_mm256_set_epi64x(INT64_C( 1902387556947256757), INT64_C(-4636290958455233996),
                             INT64_C( -193279292138890017), INT64_C( 2387678637527501964)),
      simde_mm256_set_epi64x(INT64_C(    1867272746704900), INT64_C(-6944527661819330028),
                             INT64_C(-2233693047608222631), INT64_C(   72674428659436672)) },
    { simde_mm256_set_epi64x(INT64_C(-8083909718117301567), INT64_C(   11995607010100125),
                             INT64_C(-6068617776224060223), INT64_C(-6387203967446836987)),
      simde_mm256_set_epi64x(INT64_C(-8320376883848651160), INT64_C(-4950145821323384534),
                             INT64_C(-7969688999974624617), INT64_C(  659904372446782737)),
      simde_mm256_set_epi64x(INT64_C(-8322647438183611840), INT64_C(    2406350531494152),
                             INT64_C(-9131628786599059327), INT64_C(   74330855942160641)) },
    { simde_mm256_set_epi64x(INT64_C(-7862557356832127783), INT64_C(-5197238245936512816),
                             INT64_C(-1440736387308233171), INT64_C( -422437923560182700)),
      simde_mm256_set_epi64x(INT64_C( 4501573497311276896), INT64_C( 1568099047173454230),
                             INT64_C( 6784671475384752865), INT64_C(-5901872067663085826)),
      simde_mm256_set_epi64x(INT64_C( 1324204786773460032), INT64_C( 1568098471546732688),
                             INT64_C( 5476791399028365857), INT64_C(-6196932668584612780)) },
    { simde_mm256_set_epi64x(INT64_C(  -83457062575009429), INT64_C(-7222721162513873213),
                             INT64_C( 8275972355230696496), INT64_C( 5685146925209815999)),
      simde_mm256_set_epi64x(INT64_C( 7621095561231011691), INT64_C(-1384347240916299959),
                             INT64_C( 8784701942784527649), INT64_C(-6329984144489188000)),
      simde_mm256_set_epi64x(INT64_C( 7549018173429252459), INT64_C(-8592431562369268159),
                             INT64_C( 8126746635764630560), INT64_C(  586910516468318496)) },
    { simde_mm256_set_epi64x(INT64_C( 5973184558080946927), INT64_C(-1786695518880322601),
                             INT64_C(  564422817571527071), INT64_C( 4038585732338755869)),
      simde_mm256_set_epi64x(INT64_C(-8901168232869945121), INT64_C( 8118630853720063073),
                             INT64_C( -228868271804772649), INT64_C(-6456700929251086932)),
      simde_mm256_set_epi64x(INT64_C(   27024505729917135), INT64_C( 6926573216261613633),
                             INT64_C(  346814025888696471), INT64_C( 2306177340255840524)) },
    { simde_mm256_set_epi64x(INT64_C( 4967668340414178010), INT64_C(-2410168209476403592),
                             INT64_C(-3019436090811439415), INT64_C(-6965119139859890192)),
      simde_mm256_set_epi64x(INT64_C(-5120337331222163918), INT64_C(-1589564432494918546),
                             INT64_C( 5292723257474752308), INT64_C( 2511807878775255697)),
      simde_mm256_set_epi64x(INT64_C(   67729921108361746), INT64_C(-3999169530918599576),
                             INT64_C( 4616337787987166720), INT64_C(  167381957966049936)) },
    { simde_mm256_set_epi64x(INT64_C(-6179811667909625694), INT64_C(-2471055444546593648),
                             INT64_C( 7540412455883833292), INT64_C( 6654843089135720963)),
      simde_mm256_set_epi64x(INT64_C( -939588147635733509), INT64_C(-1340596046637757449),
                             INT64_C(-1662948605324253370), INT64_C(  817158485966988858)),
      simde_mm256_set_epi64x(INT64_C(-6758530821969135454), INT64_C(-3664509346923870064),
                             INT64_C( 7540157231680104260), INT64_C(  599541701488411138)) }
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_and_si256(test_vec[i].a, test_vec[i].b);
    simde_assert_m256i_i64(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_adds_epu8(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m256i a;
    simde__m256i b;
    simde__m256i r;
  } test_vec[8] = {
    { simde_x_mm256_set_epu8(UINT8_C(253), UINT8_C(134), UINT8_C(240), UINT8_C(121),
                             UINT8_C(194), UINT8_C(  6), UINT8_C( 90), UINT8_C(185),
                             UINT8_C( 52), UINT8_C(188), UINT8_C(255), UINT8_C(213),
                             UINT8_C( 70), UINT8_C(140), UINT8_C( 59), UINT8_C(206),
                             UINT8_C( 91), UINT8_C( 56), UINT8_C(139), UINT8_C( 19),
                             UINT8_C( 62), UINT8_C( 91), UINT8_C( 24), UINT8_C( 86),
                             UINT8_C(156), UINT8_C( 89), UINT8_C( 98), UINT8_C(113),
                             UINT8_C(237), UINT8_C(  2), UINT8_C(237), UINT8_C(177)),
      simde_x_mm256_set_epu8(UINT8_C(213), UINT8_C( 63), UINT8_C( 15), UINT8_C(166),
                             UINT8_C( 63), UINT8_C(196), UINT8_C(141), UINT8_C(108),
                             UINT8_C( 47), UINT8_C(216), UINT8_C( 17), UINT8_C(218),
                             UINT8_C(111), UINT8_C(130), UINT8_C(  1), UINT8_C(159),
                             UINT8_C( 50), UINT8_C(145), UINT8_C(171), UINT8_C( 70),
                             UINT8_C( 84), UINT8_C(160), UINT8_C(222), UINT8_C(215),
                             UINT8_C( 44), UINT8_C(139), UINT8_C( 68), UINT8_C( 49),
                             UINT8_C(218), UINT8_C( 62), UINT8_C(151), UINT8_C(225)),
      simde_x_mm256_set_epu8(UINT8_C(255), UINT8_C(197), UINT8_C(255), UINT8_C(255),
                             UINT8_C(255), UINT8_C(202), UINT8_C(231), UINT8_C(255),
                             UINT8_C( 99), UINT8_C(255), UINT8_C(255), UINT8_C(255),
                             UINT8_C(181), UINT8_C(255), UINT8_C( 60), UINT8_C(255),
                             UINT8_C(141), UINT8_C(201), UINT8_C(255), UINT8_C( 89),
                             UINT8_C(146), UINT8_C(251), UINT8_C(246), UINT8_C(255),
                             UINT8_C(200), UINT8_C(228), UINT8_C(166), UINT8_C(162),
                             UINT8_C(255), UINT8_C( 64), UINT8_C(255), UINT8_C(255)) },
    { simde_x_mm256_set_epu8(UINT8_C( 46), UINT8_C( 60), UINT8_C( 83), UINT8_C( 69),
                             UINT8_C( 75), UINT8_C( 52), UINT8_C(182), UINT8_C( 56),
                             UINT8_C( 10), UINT8_C(180), UINT8_C(245), UINT8_C(208),
                             UINT8_C(165), UINT8_C( 77), UINT8_C(214), UINT8_C(172),
                             UINT8_C( 90), UINT8_C( 10), UINT8_C(190), UINT8_C(204),
                             UINT8_C(174), UINT8_C(200), UINT8_C( 75), UINT8_C(188),
                             UINT8_C(215), UINT8_C( 51), UINT8_C(188), UINT8_C( 47),
                             UINT8_C( 17), UINT8_C(116), UINT8_C(116), UINT8_C(103)),
      simde_x_mm256_set_epu8(UINT8_C( 76), UINT8_C( 23), UINT8_C( 40), UINT8_C(  7),
                             UINT8_C( 32), UINT8_C(238), UINT8_C(187), UINT8_C( 34),
                             UINT8_C(130), UINT8_C(185), UINT8_C(135), UINT8_C( 64),
                             UINT8_C(167), UINT8_C(215), UINT8_C(226), UINT8_C(221),
                             UINT8_C( 22), UINT8_C( 21), UINT8_C( 86), UINT8_C(166),
                             UINT8_C( 38), UINT8_C( 88), UINT8_C(194), UINT8_C( 97),
                             UINT8_C( 79), UINT8_C(177), UINT8_C(251), UINT8_C(218),
                             UINT8_C( 76), UINT8_C(121), UINT8_C(164), UINT8_C( 80)),
      simde_x_mm256_set_epu8(UINT8_C(122), UINT8_C( 83), UINT8_C(123), UINT8_C( 76),
                             UINT8_C(107), UINT8_C(255), UINT8_C(255), UINT8_C( 90),
                             UINT8_C(140), UINT8_C(255), UINT8_C(255), UINT8_C(255),
                             UINT8_C(255), UINT8_C(255), UINT8_C(255), UINT8_C(255),
                             UINT8_C(112), UINT8_C( 31), UINT8_C(255), UINT8_C(255),
                             UINT8_C(212), UINT8_C(255), UINT8_C(255), UINT8_C(255),
                             UINT8_C(255), UINT8_C(228), UINT8_C(255), UINT8_C(255),
                             UINT8_C( 93), UINT8_C(237), UINT8_C(255), UINT8_C(183)) },
    { simde_x_mm256_set_epu8(UINT8_C( 62), UINT8_C(125), UINT8_C(167), UINT8_C( 69),
                             UINT8_C(185), UINT8_C(211), UINT8_C(194), UINT8_C( 87),
                             UINT8_C( 42), UINT8_C( 67), UINT8_C(196), UINT8_C(131),
                             UINT8_C( 56), UINT8_C(103), UINT8_C( 93), UINT8_C(201),
                             UINT8_C(200), UINT8_C( 67), UINT8_C(  5), UINT8_C(251),
                             UINT8_C(171), UINT8_C(  0), UINT8_C(242), UINT8_C(219),
                             UINT8_C( 52), UINT8_C( 56), UINT8_C(153), UINT8_C(193),
                             UINT8_C(206), UINT8_C(184), UINT8_C(179), UINT8_C(112)),
      simde_x_mm256_set_epu8(UINT8_C(  3), UINT8_C( 94), UINT8_C(  2), UINT8_C( 80),
                             UINT8_C( 75), UINT8_C( 54), UINT8_C(116), UINT8_C(175),
                             UINT8_C(133), UINT8_C(183), UINT8_C(131), UINT8_C(  7),
                             UINT8_C( 65), UINT8_C( 80), UINT8_C(192), UINT8_C( 97),
                             UINT8_C(148), UINT8_C(232), UINT8_C(135), UINT8_C(251),
                             UINT8_C(194), UINT8_C( 84), UINT8_C(121), UINT8_C( 35),
                             UINT8_C( 55), UINT8_C(172), UINT8_C( 74), UINT8_C( 18),
                             UINT8_C( 14), UINT8_C( 11), UINT8_C( 86), UINT8_C(161)),
      simde_x_mm256_set_epu8(UINT8_C( 65), UINT8_C(219), UINT8_C(169), UINT8_C(149),
                             UINT8_C(255), UINT8_C(255), UINT8_C(255), UINT8_C(255),
                             UINT8_C(175), UINT8_C(250), UINT8_C(255), UINT8_C(138),
                             UINT8_C(121), UINT8_C(183), UINT8_C(255), UINT8_C(255),
                             UINT8_C(255), UINT8_C(255), UINT8_C(140), UINT8_C(255),
                             UINT8_C(255), UINT8_C( 84), UINT8_C(255), UINT8_C(254),
                             UINT8_C(107), UINT8_C(228), UINT8_C(227), UINT8_C(211),
                             UINT8_C(220), UINT8_C(195), UINT8_C(255), UINT8_C(255)) },
    { simde_x_mm256_set_epu8(UINT8_C(180), UINT8_C(149), UINT8_C(241), UINT8_C( 31),
                             UINT8_C( 45), UINT8_C(238), UINT8_C(127), UINT8_C( 41),
                             UINT8_C( 61), UINT8_C( 40), UINT8_C(253), UINT8_C(133),
                             UINT8_C(247), UINT8_C(164), UINT8_C(139), UINT8_C(228),
                             UINT8_C( 62), UINT8_C(209), UINT8_C(132), UINT8_C( 80),
                             UINT8_C(102), UINT8_C(192), UINT8_C(185), UINT8_C(191),
                             UINT8_C(100), UINT8_C(154), UINT8_C( 33), UINT8_C( 61),
                             UINT8_C( 93), UINT8_C(153), UINT8_C(220), UINT8_C(160)),
      simde_x_mm256_set_epu8(UINT8_C(230), UINT8_C( 84), UINT8_C( 78), UINT8_C(157),
                             UINT8_C(192), UINT8_C( 80), UINT8_C(173), UINT8_C(216),
                             UINT8_C( 47), UINT8_C(218), UINT8_C( 93), UINT8_C(143),
                             UINT8_C( 45), UINT8_C( 59), UINT8_C(151), UINT8_C(134),
                             UINT8_C( 70), UINT8_C( 90), UINT8_C( 58), UINT8_C(114),
                             UINT8_C(223), UINT8_C(242), UINT8_C( 15), UINT8_C(131),
                             UINT8_C( 82), UINT8_C(204), UINT8_C(173), UINT8_C(  5),
                             UINT8_C( 58), UINT8_C(182), UINT8_C(252), UINT8_C(237)),
      simde_x_mm256_set_epu8(UINT8_C(255), UINT8_C(233), UINT8_C(255), UINT8_C(188),
                             UINT8_C(237), UINT8_C(255), UINT8_C(255), UINT8_C(255),
                             UINT8_C(108), UINT8_C(255), UINT8_C(255), UINT8_C(255),
                             UINT8_C(255), UINT8_C(223), UINT8_C(255), UINT8_C(255),
                             UINT8_C(132), UINT8_C(255), UINT8_C(190), UINT8_C(194),
                             UINT8_C(255), UINT8_C(255), UINT8_C(200), UINT8_C(255),
                             UINT8_C(182), UINT8_C(255), UINT8_C(206), UINT8_C( 66),
                             UINT8_C(151), UINT8_C(255), UINT8_C(255), UINT8_C(255)) },
    { simde_x_mm256_set_epu8(UINT8_C(201), UINT8_C(214), UINT8_C(179), UINT8_C(233),
                             UINT8_C(198), UINT8_C( 81), UINT8_C(243), UINT8_C(119),
                             UINT8_C(160), UINT8_C(147), UINT8_C( 34), UINT8_C(138),
                             UINT8_C(127), UINT8_C( 31), UINT8_C(145), UINT8_C( 40),
                             UINT8_C(228), UINT8_C( 45), UINT8_C(  3), UINT8_C(  4),
                             UINT8_C(249), UINT8_C(180), UINT8_C(210), UINT8_C(  7),
                             UINT8_C(175), UINT8_C( 81), UINT8_C( 15), UINT8_C(137),
                             UINT8_C( 20), UINT8_C( 57), UINT8_C(  3), UINT8_C(157)),
      simde_x_mm256_set_epu8(UINT8_C(209), UINT8_C( 16), UINT8_C(253), UINT8_C(199),
                             UINT8_C(185), UINT8_C(238), UINT8_C( 28), UINT8_C( 87),
                             UINT8_C( 41), UINT8_C(232), UINT8_C( 54), UINT8_C(100),
                             UINT8_C(160), UINT8_C( 87), UINT8_C(101), UINT8_C(193),
                             UINT8_C(173), UINT8_C(242), UINT8_C(182), UINT8_C(  0),
                             UINT8_C(222), UINT8_C(142), UINT8_C(217), UINT8_C(177),
                             UINT8_C(237), UINT8_C(196), UINT8_C(145), UINT8_C(208),
                             UINT8_C( 95), UINT8_C(248), UINT8_C( 86), UINT8_C( 20)),
      simde_x_mm256_set_epu8(UINT8_C(255), UINT8_C(230), UINT8_C(255), UINT8_C(255),
                             UINT8_C(255), UINT8_C(255), UINT8_C(255), UINT8_C(206),
                             UINT8_C(201), UINT8_C(255), UINT8_C( 88), UINT8_C(238),
                             UINT8_C(255), UINT8_C(118), UINT8_C(246), UINT8_C(233),
                             UINT8_C(255), UINT8_C(255), UINT8_C(185), UINT8_C(  4),
                             UINT8_C(255), UINT8_C(255), UINT8_C(255), UINT8_C(184),
                             UINT8_C(255), UINT8_C(255), UINT8_C(160), UINT8_C(255),
                             UINT8_C(115), UINT8_C(255), UINT8_C( 89), UINT8_C(177)) },
    { simde_x_mm256_set_epu8(UINT8_C(117), UINT8_C(251), UINT8_C(156), UINT8_C( 72),
                             UINT8_C(241), UINT8_C( 25), UINT8_C( 80), UINT8_C(195),
                             UINT8_C(213), UINT8_C( 26), UINT8_C( 44), UINT8_C(154),
                             UINT8_C( 40), UINT8_C(201), UINT8_C(142), UINT8_C(110),
                             UINT8_C( 17), UINT8_C(100), UINT8_C( 41), UINT8_C(223),
                             UINT8_C(255), UINT8_C(232), UINT8_C(253), UINT8_C(190),
                             UINT8_C(155), UINT8_C(178), UINT8_C(150), UINT8_C(248),
                             UINT8_C(166), UINT8_C(223), UINT8_C( 92), UINT8_C(146)),
      simde_x_mm256_set_epu8(UINT8_C(164), UINT8_C(171), UINT8_C(230), UINT8_C(232),
                             UINT8_C( 86), UINT8_C(220), UINT8_C(153), UINT8_C(194),
                             UINT8_C( 83), UINT8_C( 81), UINT8_C( 80), UINT8_C( 93),
                             UINT8_C( 96), UINT8_C( 68), UINT8_C( 55), UINT8_C(183),
                             UINT8_C(110), UINT8_C(151), UINT8_C( 66), UINT8_C(168),
                             UINT8_C(210), UINT8_C( 58), UINT8_C(169), UINT8_C(189),
                             UINT8_C( 61), UINT8_C( 15), UINT8_C(124), UINT8_C(190),
                             UINT8_C( 93), UINT8_C(242), UINT8_C( 80), UINT8_C(225)),
      simde_x_mm256_set_epu8(UINT8_C(255), UINT8_C(255), UINT8_C(255), UINT8_C(255),
                             UINT8_C(255), UINT8_C(245), UINT8_C(233), UINT8_C(255),
                             UINT8_C(255), UINT8_C(107), UINT8_C(124), UINT8_C(247),
                             UINT8_C(136), UINT8_C(255), UINT8_C(197), UINT8_C(255),
                             UINT8_C(127), UINT8_C(251), UINT8_C(107), UINT8_C(255),
                             UINT8_C(255), UINT8_C(255), UINT8_C(255), UINT8_C(255),
                             UINT8_C(216), UINT8_C(193), UINT8_C(255), UINT8_C(255),
                             UINT8_C(255), UINT8_C(255), UINT8_C(172), UINT8_C(255)) },
    { simde_x_mm256_set_epu8(UINT8_C(130), UINT8_C( 76), UINT8_C( 98), UINT8_C(  8),
                             UINT8_C(243), UINT8_C(125), UINT8_C(189), UINT8_C(162),
                             UINT8_C(107), UINT8_C( 98), UINT8_C(171), UINT8_C( 80),
                             UINT8_C(243), UINT8_C(225), UINT8_C(  6), UINT8_C( 11),
                             UINT8_C(250), UINT8_C(210), UINT8_C( 60), UINT8_C(230),
                             UINT8_C( 17), UINT8_C(222), UINT8_C( 70), UINT8_C(180),
                             UINT8_C( 28), UINT8_C( 96), UINT8_C(128), UINT8_C(195),
                             UINT8_C(240), UINT8_C(119), UINT8_C(199), UINT8_C( 65)),
      simde_x_mm256_set_epu8(UINT8_C( 47), UINT8_C(225), UINT8_C( 74), UINT8_C(106),
                             UINT8_C(149), UINT8_C(250), UINT8_C(221), UINT8_C( 24),
                             UINT8_C(161), UINT8_C( 69), UINT8_C(209), UINT8_C(120),
                             UINT8_C(116), UINT8_C(235), UINT8_C(  4), UINT8_C(161),
                             UINT8_C(156), UINT8_C(193), UINT8_C(253), UINT8_C(  2),
                             UINT8_C(168), UINT8_C( 52), UINT8_C(231), UINT8_C(201),
                             UINT8_C(115), UINT8_C(  0), UINT8_C(176), UINT8_C(224),
                             UINT8_C(  4), UINT8_C(219), UINT8_C(202), UINT8_C(177)),
      simde_x_mm256_set_epu8(UINT8_C(177), UINT8_C(255), UINT8_C(172), UINT8_C(114),
                             UINT8_C(255), UINT8_C(255), UINT8_C(255), UINT8_C(186),
                             UINT8_C(255), UINT8_C(167), UINT8_C(255), UINT8_C(200),
                             UINT8_C(255), UINT8_C(255), UINT8_C( 10), UINT8_C(172),
                             UINT8_C(255), UINT8_C(255), UINT8_C(255), UINT8_C(232),
                             UINT8_C(185), UINT8_C(255), UINT8_C(255), UINT8_C(255),
                             UINT8_C(143), UINT8_C( 96), UINT8_C(255), UINT8_C(255),
                             UINT8_C(244), UINT8_C(255), UINT8_C(255), UINT8_C(242)) },
    { simde_x_mm256_set_epu8(UINT8_C(144), UINT8_C( 62), UINT8_C(142), UINT8_C(211),
                             UINT8_C( 41), UINT8_C(162), UINT8_C(184), UINT8_C(180),
                             UINT8_C(242), UINT8_C( 80), UINT8_C( 73), UINT8_C( 63),
                             UINT8_C(168), UINT8_C(176), UINT8_C( 12), UINT8_C( 85),
                             UINT8_C( 62), UINT8_C( 83), UINT8_C( 52), UINT8_C( 39),
                             UINT8_C( 56), UINT8_C(245), UINT8_C( 65), UINT8_C(213),
                             UINT8_C( 94), UINT8_C( 88), UINT8_C(157), UINT8_C(124),
                             UINT8_C(123), UINT8_C(196), UINT8_C( 79), UINT8_C( 49)),
      simde_x_mm256_set_epu8(UINT8_C(142), UINT8_C( 71), UINT8_C(103), UINT8_C(139),
                             UINT8_C(236), UINT8_C(100), UINT8_C(139), UINT8_C(154),
                             UINT8_C(203), UINT8_C(125), UINT8_C(237), UINT8_C(236),
                             UINT8_C( 45), UINT8_C(103), UINT8_C( 56), UINT8_C( 68),
                             UINT8_C( 26), UINT8_C( 73), UINT8_C(130), UINT8_C( 19),
                             UINT8_C(222), UINT8_C(206), UINT8_C(129), UINT8_C(101),
                             UINT8_C( 56), UINT8_C(145), UINT8_C(213), UINT8_C(249),
                             UINT8_C(145), UINT8_C( 67), UINT8_C(236), UINT8_C(136)),
      simde_x_mm256_set_epu8(UINT8_C(255), UINT8_C(133), UINT8_C(245), UINT8_C(255),
                             UINT8_C(255), UINT8_C(255), UINT8_C(255), UINT8_C(255),
                             UINT8_C(255), UINT8_C(205), UINT8_C(255), UINT8_C(255),
                             UINT8_C(213), UINT8_C(255), UINT8_C( 68), UINT8_C(153),
                             UINT8_C( 88), UINT8_C(156), UINT8_C(182), UINT8_C( 58),
                             UINT8_C(255), UINT8_C(255), UINT8_C(194), UINT8_C(255),
                             UINT8_C(150), UINT8_C(233), UINT8_C(255), UINT8_C(255),
                             UINT8_C(255), UINT8_C(255), UINT8_C(255), UINT8_C(185)) },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_adds_epu8(test_vec[i].a, test_vec[i].b);
    simde_assert_m256i_u8(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_blendv_epi8(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m256i a;
    simde__m256i b;
    simde__m256i i;
    simde__m256i r;
  } test_vec[8] = {
    { simde_mm256_set_epi8(INT8_C( 119), INT8_C(  14), INT8_C( 127), INT8_C(-117),
                           INT8_C( -92), INT8_C(  49), INT8_C( -15), INT8_C( -64),
                           INT8_C(  66), INT8_C(-125), INT8_C(  43), INT8_C(   6),
                           INT8_C(-117), INT8_C(  95), INT8_C(   4), INT8_C( 100),
                           INT8_C(  82), INT8_C( -66), INT8_C(  57), INT8_C( -98),
                           INT8_C( -94), INT8_C(   7), INT8_C(  58), INT8_C(-109),
                           INT8_C( -21), INT8_C( -88), INT8_C(  12), INT8_C(  65),
                           INT8_C(-108), INT8_C( -25), INT8_C( -96), INT8_C(  -4)),
      simde_mm256_set_epi8(INT8_C( -68), INT8_C(  -8), INT8_C(  57), INT8_C( 103),
                           INT8_C(  55), INT8_C( 120), INT8_C(   1), INT8_C(  68),
                           INT8_C(  85), INT8_C(-119), INT8_C(  -3), INT8_C(  60),
                           INT8_C(-115), INT8_C( -64), INT8_C( 126), INT8_C( -67),
                           INT8_C(  11), INT8_C(  73), INT8_C(  97), INT8_C( -47),
                           INT8_C(  73), INT8_C( -17), INT8_C(  -4), INT8_C(  19),
                           INT8_C( -66), INT8_C(  -1), INT8_C(  84), INT8_C( -63),
                           INT8_C(  58), INT8_C( 114), INT8_C( 107), INT8_C( -13)),
      simde_mm256_set_epi8(INT8_C( -94), INT8_C( -13), INT8_C( -63), INT8_C(  48),
                           INT8_C(  72), INT8_C( -33), INT8_C(-118), INT8_C(  86),
                           INT8_C(  17), INT8_C( 112), INT8_C(   9), INT8_C( 106),
                           INT8_C( 115), INT8_C( -15), INT8_C(  74), INT8_C(   5),
                           INT8_C(  17), INT8_C( -31), INT8_C(-120), INT8_C(  18),
                           INT8_C(  82), INT8_C( -67), INT8_C(-101), INT8_C(-109),
                           INT8_C(  81), INT8_C(-126), INT8_C(  -8), INT8_C(   4),
                           INT8_C( 123), INT8_C( 125), INT8_C(  70), INT8_C(  66)),
      simde_mm256_set_epi8(INT8_C( -68), INT8_C(  -8), INT8_C(  57), INT8_C(-117),
                           INT8_C( -92), INT8_C( 120), INT8_C(   1), INT8_C( -64),
                           INT8_C(  66), INT8_C(-125), INT8_C(  43), INT8_C(   6),
                           INT8_C(-117), INT8_C( -64), INT8_C(   4), INT8_C( 100),
                           INT8_C(  82), INT8_C(  73), INT8_C(  97), INT8_C( -98),
                           INT8_C( -94), INT8_C( -17), INT8_C(  -4), INT8_C(  19),
                           INT8_C( -21), INT8_C(  -1), INT8_C(  84), INT8_C(  65),
                           INT8_C(-108), INT8_C( -25), INT8_C( -96), INT8_C(  -4)) },
    { simde_mm256_set_epi8(INT8_C( -95), INT8_C(  48), INT8_C(-106), INT8_C(   2),
                           INT8_C( -98), INT8_C(  42), INT8_C( 111), INT8_C( -63),
                           INT8_C(  63), INT8_C(  60), INT8_C(-104), INT8_C(-108),
                           INT8_C( -18), INT8_C( -88), INT8_C(  55), INT8_C(  21),
                           INT8_C(-103), INT8_C( 114), INT8_C( -80), INT8_C(  89),
                           INT8_C(  60), INT8_C(  45), INT8_C( -20), INT8_C(  79),
                           INT8_C(-112), INT8_C( -14), INT8_C( -11), INT8_C( 117),
                           INT8_C(  14), INT8_C( -21), INT8_C(  11), INT8_C(-119)),
      simde_mm256_set_epi8(INT8_C(   7), INT8_C( -82), INT8_C( -49), INT8_C(   6),
                           INT8_C(-108), INT8_C(-115), INT8_C( -95), INT8_C( -53),
                           INT8_C(   6), INT8_C(  28), INT8_C(  47), INT8_C(  86),
                           INT8_C( -76), INT8_C(-114), INT8_C( 114), INT8_C(  94),
                           INT8_C(  90), INT8_C(  13), INT8_C( 121), INT8_C(-123),
                           INT8_C( -33), INT8_C( -67), INT8_C(  30), INT8_C( -90),
                           INT8_C(  -5), INT8_C(  42), INT8_C( 102), INT8_C(  53),
                           INT8_C(  95), INT8_C(  56), INT8_C(   1), INT8_C( -15)),
      simde_mm256_set_epi8(INT8_C(-117), INT8_C( -35), INT8_C(  72), INT8_C( -41),
                           INT8_C(-118), INT8_C( 110), INT8_C(  61), INT8_C(  45),
                           INT8_C(-112), INT8_C( 112), INT8_C(  46), INT8_C( -75),
                           INT8_C(  71), INT8_C( -85), INT8_C( -58), INT8_C( 104),
                           INT8_C(-126), INT8_C(-109), INT8_C(  86), INT8_C(  70),
                           INT8_C( -85), INT8_C( 113), INT8_C(  90), INT8_C(  35),
                           INT8_C( -48), INT8_C( -83), INT8_C(  16), INT8_C(  55),
                           INT8_C( -13), INT8_C(  42), INT8_C( -55), INT8_C( -15)),
      simde_mm256_set_epi8(INT8_C(   7), INT8_C( -82), INT8_C(-106), INT8_C(   6),
                           INT8_C(-108), INT8_C(  42), INT8_C( 111), INT8_C( -63),
                           INT8_C(   6), INT8_C(  60), INT8_C(-104), INT8_C(  86),
                           INT8_C( -18), INT8_C(-114), INT8_C( 114), INT8_C(  21),
                           INT8_C(  90), INT8_C(  13), INT8_C( -80), INT8_C(  89),
                           INT8_C( -33), INT8_C(  45), INT8_C( -20), INT8_C(  79),
                           INT8_C(  -5), INT8_C(  42), INT8_C( -11), INT8_C( 117),
                           INT8_C(  95), INT8_C( -21), INT8_C(   1), INT8_C( -15)) },
    { simde_mm256_set_epi8(INT8_C(  12), INT8_C( 118), INT8_C(-120), INT8_C(  17),
                           INT8_C(  61), INT8_C(  24), INT8_C(-114), INT8_C(-117),
                           INT8_C( -20), INT8_C(-118), INT8_C(  93), INT8_C( 106),
                           INT8_C( -99), INT8_C(  -8), INT8_C( 114), INT8_C(-115),
                           INT8_C( -65), INT8_C( -34), INT8_C(  66), INT8_C(  62),
                           INT8_C( 113), INT8_C( -44), INT8_C( 109), INT8_C(  20),
                           INT8_C( 122), INT8_C( -58), INT8_C(   7), INT8_C(-123),
                           INT8_C(  18), INT8_C(  89), INT8_C( -84), INT8_C(-114)),
      simde_mm256_set_epi8(INT8_C( -67), INT8_C( -15), INT8_C( -72), INT8_C( -39),
                           INT8_C( -90), INT8_C( 108), INT8_C(  93), INT8_C( -36),
                           INT8_C( -64), INT8_C(  36), INT8_C( -98), INT8_C(  76),
                           INT8_C( 123), INT8_C( -40), INT8_C( -48), INT8_C(-111),
                           INT8_C(-100), INT8_C(  76), INT8_C( 114), INT8_C(  51),
                           INT8_C(  72), INT8_C(  51), INT8_C( 101), INT8_C(-128),
                           INT8_C( -68), INT8_C(  35), INT8_C( -50), INT8_C(-100),
                           INT8_C(  85), INT8_C(-109), INT8_C( -86), INT8_C(  43)),
      simde_mm256_set_epi8(INT8_C(  21), INT8_C(  44), INT8_C(  93), INT8_C( -14),
                           INT8_C(  76), INT8_C(  78), INT8_C( 101), INT8_C(  40),
                           INT8_C( 126), INT8_C( -37), INT8_C( 115), INT8_C(  17),
                           INT8_C(  43), INT8_C( -71), INT8_C(-123), INT8_C( -85),
                           INT8_C( -19), INT8_C(  27), INT8_C(  72), INT8_C(  57),
                           INT8_C( 118), INT8_C( -19), INT8_C( -66), INT8_C( 124),
                           INT8_C( -52), INT8_C( -69), INT8_C(  32), INT8_C(  64),
                           INT8_C( -16), INT8_C(-103), INT8_C( -39), INT8_C( 121)),
      simde_mm256_set_epi8(INT8_C(  12), INT8_C( 118), INT8_C(-120), INT8_C( -39),
                           INT8_C(  61), INT8_C(  24), INT8_C(-114), INT8_C(-117),
                           INT8_C( -20), INT8_C(  36), INT8_C(  93), INT8_C( 106),
                           INT8_C( -99), INT8_C( -40), INT8_C( -48), INT8_C(-111),
                           INT8_C(-100), INT8_C( -34), INT8_C(  66), INT8_C(  62),
                           INT8_C( 113), INT8_C(  51), INT8_C( 101), INT8_C(  20),
                           INT8_C( -68), INT8_C(  35), INT8_C(   7), INT8_C(-123),
                           INT8_C(  85), INT8_C(-109), INT8_C( -86), INT8_C(-114)) },
    { simde_mm256_set_epi8(INT8_C( -23), INT8_C( 109), INT8_C(  45), INT8_C( -63),
                           INT8_C(  54), INT8_C( -58), INT8_C( -11), INT8_C(  18),
                           INT8_C(  27), INT8_C( -68), INT8_C(-102), INT8_C(  76),
                           INT8_C( -97), INT8_C(  26), INT8_C(  10), INT8_C( -41),
                           INT8_C(  50), INT8_C(  54), INT8_C(-128), INT8_C(  77),
                           INT8_C( -33), INT8_C( -46), INT8_C( 118), INT8_C(  76),
                           INT8_C( -72), INT8_C( 106), INT8_C( -54), INT8_C(  28),
                           INT8_C(  86), INT8_C(  37), INT8_C(  -1), INT8_C(  83)),
      simde_mm256_set_epi8(INT8_C( 123), INT8_C(  58), INT8_C(  98), INT8_C( 125),
                           INT8_C( 118), INT8_C(-119), INT8_C( -36), INT8_C(  78),
                           INT8_C(   0), INT8_C(  77), INT8_C(  67), INT8_C( 118),
                           INT8_C(  22), INT8_C( -94), INT8_C( -70), INT8_C(  21),
                           INT8_C(  65), INT8_C(  89), INT8_C(  34), INT8_C(  21),
                           INT8_C(  65), INT8_C( -53), INT8_C( -43), INT8_C( -55),
                           INT8_C( -12), INT8_C( -79), INT8_C(-123), INT8_C(  80),
                           INT8_C( -58), INT8_C( -76), INT8_C( -82), INT8_C(  16)),
      simde_mm256_set_epi8(INT8_C( -15), INT8_C( -31), INT8_C( 124), INT8_C(  18),
                           INT8_C(  63), INT8_C(-119), INT8_C( -84), INT8_C( -47),
                           INT8_C( 110), INT8_C(  99), INT8_C(  -7), INT8_C( -78),
                           INT8_C( 122), INT8_C(   9), INT8_C(  54), INT8_C(-112),
                           INT8_C(-100), INT8_C(  -9), INT8_C(-127), INT8_C(  67),
                           INT8_C( -60), INT8_C( -43), INT8_C(  76), INT8_C(  10),
                           INT8_C(  83), INT8_C( -83), INT8_C( -60), INT8_C( -94),
                           INT8_C( -63), INT8_C( 113), INT8_C(-114), INT8_C( 124)),
      simde_mm256_set_epi8(INT8_C( 123), INT8_C(  58), INT8_C(  45), INT8_C( -63),
                           INT8_C(  54), INT8_C(-119), INT8_C( -36), INT8_C(  78),
                           INT8_C(  27), INT8_C( -68), INT8_C(  67), INT8_C( 118),
                           INT8_C( -97), INT8_C(  26), INT8_C(  10), INT8_C(  21),
                           INT8_C(  65), INT8_C(  89), INT8_C(  34), INT8_C(  77),
                           INT8_C(  65), INT8_C( -53), INT8_C( 118), INT8_C(  76),
                           INT8_C( -72), INT8_C( -79), INT8_C(-123), INT8_C(  80),
                           INT8_C( -58), INT8_C(  37), INT8_C( -82), INT8_C(  83)) },
    { simde_mm256_set_epi8(INT8_C(  71), INT8_C(  12), INT8_C( 123), INT8_C(-112),
                           INT8_C(-126), INT8_C(  60), INT8_C( 108), INT8_C(-103),
                           INT8_C( 103), INT8_C( 120), INT8_C( -99), INT8_C( 114),
                           INT8_C(  34), INT8_C( -37), INT8_C( -98), INT8_C( -39),
                           INT8_C(-107), INT8_C( -14), INT8_C(  -8), INT8_C( -82),
                           INT8_C( 123), INT8_C(  78), INT8_C(  27), INT8_C(   7),
                           INT8_C(  90), INT8_C(-108), INT8_C( -54), INT8_C(  40),
                           INT8_C(  -9), INT8_C( -18), INT8_C(  12), INT8_C(   6)),
      simde_mm256_set_epi8(INT8_C(  20), INT8_C( -98), INT8_C(  96), INT8_C(   3),
                           INT8_C(  27), INT8_C(  45), INT8_C( -97), INT8_C( -19),
                           INT8_C( -40), INT8_C( -84), INT8_C( -70), INT8_C( -38),
                           INT8_C( -57), INT8_C(-122), INT8_C( -18), INT8_C( -59),
                           INT8_C( -66), INT8_C(  38), INT8_C(  28), INT8_C( -72),
                           INT8_C(  41), INT8_C( -85), INT8_C(-107), INT8_C( 124),
                           INT8_C(-120), INT8_C(   0), INT8_C(  52), INT8_C( -73),
                           INT8_C( -94), INT8_C(-103), INT8_C( 104), INT8_C(-108)),
      simde_mm256_set_epi8(INT8_C( 114), INT8_C(  67), INT8_C(  87), INT8_C(  60),
                           INT8_C( -47), INT8_C(-121), INT8_C( -54), INT8_C( 110),
                           INT8_C(-100), INT8_C( 105), INT8_C( -23), INT8_C(  81),
                           INT8_C(-121), INT8_C(  67), INT8_C(  97), INT8_C(-125),
                           INT8_C(  78), INT8_C( 118), INT8_C(  46), INT8_C( -85),
                           INT8_C(  78), INT8_C( -66), INT8_C(  11), INT8_C(  90),
                           INT8_C(  11), INT8_C( 120), INT8_C(  20), INT8_C(  83),
                           INT8_C( 103), INT8_C( -43), INT8_C(  72), INT8_C( -92)),
      simde_mm256_set_epi8(INT8_C(  71), INT8_C(  12), INT8_C( 123), INT8_C(-112),
                           INT8_C(  27), INT8_C(  45), INT8_C( -97), INT8_C(-103),
                           INT8_C( -40), INT8_C( 120), INT8_C( -70), INT8_C( 114),
                           INT8_C( -57), INT8_C( -37), INT8_C( -98), INT8_C( -59),
                           INT8_C(-107), INT8_C( -14), INT8_C(  -8), INT8_C( -72),
                           INT8_C( 123), INT8_C( -85), INT8_C(  27), INT8_C(   7),
                           INT8_C(  90), INT8_C(-108), INT8_C( -54), INT8_C(  40),
                           INT8_C(  -9), INT8_C(-103), INT8_C(  12), INT8_C(-108)) },
    { simde_mm256_set_epi8(INT8_C(-120), INT8_C( -17), INT8_C(  71), INT8_C( 108),
                           INT8_C(-124), INT8_C(   8), INT8_C(  38), INT8_C(-124),
                           INT8_C( -33), INT8_C( -80), INT8_C(  82), INT8_C( -52),
                           INT8_C( -85), INT8_C(  20), INT8_C( -43), INT8_C(  49),
                           INT8_C(-127), INT8_C(  82), INT8_C(-125), INT8_C(-107),
                           INT8_C(  99), INT8_C( -94), INT8_C(  98), INT8_C( 124),
                           INT8_C(  23), INT8_C(  -8), INT8_C( -30), INT8_C( 107),
                           INT8_C( -17), INT8_C( -36), INT8_C(  65), INT8_C(  35)),
      simde_mm256_set_epi8(INT8_C(  50), INT8_C( -42), INT8_C(  70), INT8_C(  74),
                           INT8_C( -25), INT8_C( 118), INT8_C(  53), INT8_C(  91),
                           INT8_C( -24), INT8_C(  44), INT8_C(-107), INT8_C(  38),
                           INT8_C(  62), INT8_C(  93), INT8_C(  84), INT8_C(  86),
                           INT8_C(  25), INT8_C(  25), INT8_C(  -1), INT8_C( -49),
                           INT8_C( -69), INT8_C( -81), INT8_C(  33), INT8_C( -90),
                           INT8_C( 118), INT8_C(  99), INT8_C( -68), INT8_C(  38),
                           INT8_C( -18), INT8_C( -20), INT8_C( -37), INT8_C( -57)),
      simde_mm256_set_epi8(INT8_C(  36), INT8_C(  48), INT8_C(-118), INT8_C( 125),
                           INT8_C(  12), INT8_C( 115), INT8_C( -38), INT8_C(   1),
                           INT8_C( -43), INT8_C(-120), INT8_C( 119), INT8_C(  88),
                           INT8_C(  19), INT8_C(   1), INT8_C(  40), INT8_C( -39),
                           INT8_C( -67), INT8_C(  66), INT8_C( -86), INT8_C(  38),
                           INT8_C(  40), INT8_C( -46), INT8_C( 104), INT8_C( -95),
                           INT8_C( 115), INT8_C( -49), INT8_C(  15), INT8_C(-101),
                           INT8_C( -79), INT8_C(  -5), INT8_C( 112), INT8_C( -45)),
      simde_mm256_set_epi8(INT8_C(-120), INT8_C( -17), INT8_C(  70), INT8_C( 108),
                           INT8_C(-124), INT8_C(   8), INT8_C(  53), INT8_C(-124),
                           INT8_C( -24), INT8_C(  44), INT8_C(  82), INT8_C( -52),
                           INT8_C( -85), INT8_C(  20), INT8_C( -43), INT8_C(  86),
                           INT8_C(  25), INT8_C(  82), INT8_C(  -1), INT8_C(-107),
                           INT8_C(  99), INT8_C( -81), INT8_C(  98), INT8_C( -90),
                           INT8_C(  23), INT8_C(  99), INT8_C( -30), INT8_C(  38),
                           INT8_C( -18), INT8_C( -20), INT8_C(  65), INT8_C( -57)) },
    { simde_mm256_set_epi8(INT8_C(  55), INT8_C(  33), INT8_C(  43), INT8_C(  65),
                           INT8_C( -59), INT8_C( -95), INT8_C(  10), INT8_C(  11),
                           INT8_C( 122), INT8_C(  35), INT8_C(  55), INT8_C( 107),
                           INT8_C( -46), INT8_C(-119), INT8_C(-106), INT8_C(  77),
                           INT8_C( -56), INT8_C( -78), INT8_C( -97), INT8_C(-126),
                           INT8_C( -36), INT8_C(  17), INT8_C(  13), INT8_C(  38),
                           INT8_C(  52), INT8_C( -31), INT8_C(  68), INT8_C(  51),
                           INT8_C( -16), INT8_C(  61), INT8_C( -72), INT8_C( -48)),
      simde_mm256_set_epi8(INT8_C( 123), INT8_C(-111), INT8_C( -83), INT8_C(  -8),
                           INT8_C(  66), INT8_C( -69), INT8_C( -27), INT8_C(-103),
                           INT8_C(-112), INT8_C( -80), INT8_C(  56), INT8_C(  60),
                           INT8_C(-106), INT8_C(  -4), INT8_C(-128), INT8_C(-122),
                           INT8_C(  74), INT8_C( -55), INT8_C( -48), INT8_C(-128),
                           INT8_C(  -2), INT8_C(  63), INT8_C( -37), INT8_C(  18),
                           INT8_C( -89), INT8_C( -76), INT8_C(  42), INT8_C(  62),
                           INT8_C(  74), INT8_C( -87), INT8_C(  30), INT8_C(-103)),
      simde_mm256_set_epi8(INT8_C(   4), INT8_C( -10), INT8_C(  -5), INT8_C(  -1),
                           INT8_C(  -4), INT8_C(  87), INT8_C( -59), INT8_C(  -9),
                           INT8_C( -53), INT8_C(  83), INT8_C( -63), INT8_C(  99),
                           INT8_C(  55), INT8_C( 119), INT8_C(  36), INT8_C( -96),
                           INT8_C( -98), INT8_C(  22), INT8_C(   4), INT8_C(-128),
                           INT8_C(  16), INT8_C( -72), INT8_C( 114), INT8_C(  35),
                           INT8_C( -15), INT8_C( -10), INT8_C(  97), INT8_C(-112),
                           INT8_C(-109), INT8_C( -68), INT8_C(   8), INT8_C( 101)),
      simde_mm256_set_epi8(INT8_C(  55), INT8_C(-111), INT8_C( -83), INT8_C(  -8),
                           INT8_C(  66), INT8_C( -95), INT8_C( -27), INT8_C(-103),
                           INT8_C(-112), INT8_C(  35), INT8_C(  56), INT8_C( 107),
                           INT8_C( -46), INT8_C(-119), INT8_C(-106), INT8_C(-122),
                           INT8_C(  74), INT8_C( -78), INT8_C( -97), INT8_C(-128),
                           INT8_C( -36), INT8_C(  63), INT8_C(  13), INT8_C(  38),
                           INT8_C( -89), INT8_C( -76), INT8_C(  68), INT8_C(  62),
                           INT8_C(  74), INT8_C( -87), INT8_C( -72), INT8_C( -48)) },
    { simde_mm256_set_epi8(INT8_C(  69), INT8_C( -38), INT8_C(-105), INT8_C( -77),
                           INT8_C(   3), INT8_C( -19), INT8_C( -91), INT8_C(  81),
                           INT8_C( -61), INT8_C(  88), INT8_C( -52), INT8_C( -76),
                           INT8_C(-100), INT8_C( -70), INT8_C( -64), INT8_C(  71),
                           INT8_C(  82), INT8_C(-122), INT8_C( -41), INT8_C( -86),
                           INT8_C(   9), INT8_C(  29), INT8_C( -31), INT8_C( -87),
                           INT8_C(-113), INT8_C( 100), INT8_C( 100), INT8_C( -55),
                           INT8_C( -11), INT8_C(  92), INT8_C( -87), INT8_C(  43)),
      simde_mm256_set_epi8(INT8_C(  96), INT8_C(-116), INT8_C(   5), INT8_C(  16),
                           INT8_C( -66), INT8_C(   4), INT8_C(   8), INT8_C(  34),
                           INT8_C(  93), INT8_C(  90), INT8_C( -27), INT8_C(  86),
                           INT8_C( 115), INT8_C(  27), INT8_C( -30), INT8_C(  15),
                           INT8_C(  94), INT8_C( -93), INT8_C( -55), INT8_C( -18),
                           INT8_C(-122), INT8_C(  51), INT8_C( -22), INT8_C( -72),
                           INT8_C( -80), INT8_C(  24), INT8_C(  38), INT8_C(  87),
                           INT8_C( -35), INT8_C( -67), INT8_C(  94), INT8_C( -17)),
      simde_mm256_set_epi8(INT8_C( -19), INT8_C( -11), INT8_C(  77), INT8_C( -75),
                           INT8_C(  98), INT8_C( -18), INT8_C( -28), INT8_C(   5),
                           INT8_C(  86), INT8_C(-117), INT8_C( 114), INT8_C( -52),
                           INT8_C(  63), INT8_C( -51), INT8_C( 110), INT8_C( -22),
                           INT8_C(  54), INT8_C(  36), INT8_C(  44), INT8_C(  72),
                           INT8_C( -14), INT8_C( -61), INT8_C( -76), INT8_C(  51),
                           INT8_C(  40), INT8_C( -28), INT8_C( -97), INT8_C( 114),
                           INT8_C(-128), INT8_C(   9), INT8_C(  94), INT8_C( -35)),
      simde_mm256_set_epi8(INT8_C(  96), INT8_C(-116), INT8_C(-105), INT8_C(  16),
                           INT8_C(   3), INT8_C(   4), INT8_C(   8), INT8_C(  81),
                           INT8_C( -61), INT8_C(  90), INT8_C( -52), INT8_C(  86),
                           INT8_C(-100), INT8_C(  27), INT8_C( -64), INT8_C(  15),
                           INT8_C(  82), INT8_C(-122), INT8_C( -41), INT8_C( -86),
                           INT8_C(-122), INT8_C(  51), INT8_C( -22), INT8_C( -87),
                           INT8_C(-113), INT8_C(  24), INT8_C(  38), INT8_C( -55),
                           INT8_C( -35), INT8_C(  92), INT8_C( -87), INT8_C( -17)) },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_blendv_epi8(test_vec[i].a, test_vec[i].b, test_vec[i].i);
    simde_assert_m256i_i8(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_cmpgt_epi32(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m256i a;
    simde__m256i b;
    simde__m256i r;
  } test_vec[8] = {
    { simde_mm256_set_epi32(INT32_C(-1910963751), INT32_C(-1037527336), INT32_C( -581253082), INT32_C( -805157505),
                            INT32_C( 1446966287), INT32_C(   -8913681), INT32_C( -494526366), INT32_C(-1857474161)),
      simde_mm256_set_epi32(INT32_C(-1143050049), INT32_C(-1545949366), INT32_C( 1503277288), INT32_C(-1357138171),
                            INT32_C( 1058844939), INT32_C(  309480335), INT32_C( 1825640960), INT32_C(-2083253752)),
      simde_mm256_set_epi32(INT32_C(          0), INT32_C(         -1), INT32_C(          0), INT32_C(         -1),
                            INT32_C(         -1), INT32_C(          0), INT32_C(          0), INT32_C(         -1)) },
    { simde_mm256_set_epi32(INT32_C(-1125895018), INT32_C( -151199733), INT32_C(-1156572232), INT32_C(-1719423594),
                            INT32_C(-1350415044), INT32_C( 1941048360), INT32_C( 1462693644), INT32_C(  157276070)),
      simde_mm256_set_epi32(INT32_C( 1685470989), INT32_C(  -23549807), INT32_C( 2101982138), INT32_C(-1846214249),
                            INT32_C(-1855916776), INT32_C( -540831398), INT32_C(  233301808), INT32_C( 1667068415)),
      simde_mm256_set_epi32(INT32_C(          0), INT32_C(          0), INT32_C(          0), INT32_C(         -1),
                            INT32_C(         -1), INT32_C(         -1), INT32_C(         -1), INT32_C(          0)) },
    { simde_mm256_set_epi32(INT32_C(-2064202369), INT32_C( -937796718), INT32_C( 1860922821), INT32_C( -943515104),
                            INT32_C( 1932702217), INT32_C(-1909235607), INT32_C( -701927701), INT32_C( 2122537608)),
      simde_mm256_set_epi32(INT32_C( 1359427872), INT32_C(  430067405), INT32_C(-2017266204), INT32_C( -112174075),
                            INT32_C(-2036257158), INT32_C(  794990098), INT32_C( 1595368835), INT32_C(-2025748789)),
      simde_mm256_set_epi32(INT32_C(          0), INT32_C(          0), INT32_C(         -1), INT32_C(          0),
                            INT32_C(         -1), INT32_C(          0), INT32_C(          0), INT32_C(         -1)) },
    { simde_mm256_set_epi32(INT32_C(  101914014), INT32_C( 1252307439), INT32_C( -251229086), INT32_C( 1747655874),
                            INT32_C( 1975156439), INT32_C(  244588822), INT32_C(-2030488384), INT32_C(  -41784348)),
      simde_mm256_set_epi32(INT32_C(  126704158), INT32_C(-1817043660), INT32_C(   67229317), INT32_C( 1709840887),
                            INT32_C( -401701180), INT32_C(-1816869894), INT32_C( -356935412), INT32_C( 1029497038)),
      simde_mm256_set_epi32(INT32_C(          0), INT32_C(         -1), INT32_C(          0), INT32_C(         -1),
                            INT32_C(         -1), INT32_C(         -1), INT32_C(          0), INT32_C(          0)) },
    { simde_mm256_set_epi32(INT32_C(-1821031073), INT32_C(-1888821389), INT32_C( 1302274763), INT32_C( -889069785),
                            INT32_C(  849224332), INT32_C( 1448513971), INT32_C(-1444618137), INT32_C( -857531383)),
      simde_mm256_set_epi32(INT32_C( -294182987), INT32_C(-1911426210), INT32_C( 1273887477), INT32_C( -804272895),
                            INT32_C(-1138168885), INT32_C(-1273049807), INT32_C( -920424822), INT32_C(   75748881)),
      simde_mm256_set_epi32(INT32_C(          0), INT32_C(         -1), INT32_C(         -1), INT32_C(          0),
                            INT32_C(         -1), INT32_C(         -1), INT32_C(          0), INT32_C(          0)) },
    { simde_mm256_set_epi32(INT32_C( -145989095), INT32_C( 1224886052), INT32_C(-1270092347), INT32_C(-2004839127),
                            INT32_C( -805168375), INT32_C(-2053011497), INT32_C(  926069792), INT32_C( -523797780)),
      simde_mm256_set_epi32(INT32_C( 1782736183), INT32_C( 1196895214), INT32_C( 2023829967), INT32_C(  431966763),
                            INT32_C(-1279096565), INT32_C(-1568278654), INT32_C( -225755322), INT32_C(  800135833)),
      simde_mm256_set_epi32(INT32_C(          0), INT32_C(         -1), INT32_C(          0), INT32_C(          0),
                            INT32_C(         -1), INT32_C(          0), INT32_C(         -1), INT32_C(          0)) },
    { simde_mm256_set_epi32(INT32_C(   45181175), INT32_C( 2067174734), INT32_C(-1046962322), INT32_C( -770870625),
                            INT32_C(  166196701), INT32_C(-1211694319), INT32_C( 1891438592), INT32_C(-1986783509)),
      simde_mm256_set_epi32(INT32_C( 1357811899), INT32_C( -666006860), INT32_C(  -78093915), INT32_C(-1784875915),
                            INT32_C(-1592390514), INT32_C( -295345562), INT32_C(-1194315003), INT32_C( -378378269)),
      simde_mm256_set_epi32(INT32_C(          0), INT32_C(         -1), INT32_C(          0), INT32_C(         -1),
                            INT32_C(         -1), INT32_C(          0), INT32_C(         -1), INT32_C(          0)) },
    { simde_mm256_set_epi32(INT32_C( 2029570724), INT32_C(  593067919), INT32_C( 1378001411), INT32_C(-1490077172),
                            INT32_C( -985008502), INT32_C( -780769236), INT32_C(  983706005), INT32_C( -145048806)),
      simde_mm256_set_epi32(INT32_C( -371614648), INT32_C(  790968401), INT32_C(  604322541), INT32_C( 1275463353),
                            INT32_C(  507685025), INT32_C(-1785065497), INT32_C( -324987069), INT32_C( 1403024939)),
      simde_mm256_set_epi32(INT32_C(         -1), INT32_C(          0), INT32_C(         -1), INT32_C(          0),
                            INT32_C(          0), INT32_C(         -1), INT32_C(         -1), INT32_C(          0)) },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_cmpgt_epi32(test_vec[i].a, test_vec[i].b);
    simde_assert_m256i_i32(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_broadcastsi128_si256(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m128i a;
    simde__m256i r;
  } test_vec[8] = {
    { simde_mm_set_epi64x   (INT64_C( 3783485884510153131), INT64_C( 5322848723863790661)),
      simde_mm256_set_epi64x(INT64_C( 3783485884510153131), INT64_C( 5322848723863790661),
                             INT64_C( 3783485884510153131), INT64_C( 5322848723863790661)) },
    { simde_mm_set_epi64x   (INT64_C( 3709494745882156155), INT64_C(-6688158465955285293)),
      simde_mm256_set_epi64x(INT64_C( 3709494745882156155), INT64_C(-6688158465955285293),
                             INT64_C( 3709494745882156155), INT64_C(-6688158465955285293)) },
    { simde_mm_set_epi64x   (INT64_C(-8419237038829073489), INT64_C(-1707044583358729761)),
      simde_mm256_set_epi64x(INT64_C(-8419237038829073489), INT64_C(-1707044583358729761),
                             INT64_C(-8419237038829073489), INT64_C(-1707044583358729761)) },
    { simde_mm_set_epi64x   (INT64_C( -168447772491176834), INT64_C(-4784151950425519944)),
      simde_mm256_set_epi64x(INT64_C( -168447772491176834), INT64_C(-4784151950425519944),
                             INT64_C( -168447772491176834), INT64_C(-4784151950425519944)) },
    { simde_mm_set_epi64x   (INT64_C(  992172666234330248), INT64_C( 7115358650695109080)),
      simde_mm256_set_epi64x(INT64_C(  992172666234330248), INT64_C( 7115358650695109080),
                             INT64_C(  992172666234330248), INT64_C( 7115358650695109080)) },
    { simde_mm_set_epi64x   (INT64_C( 6019682307676879898), INT64_C( -745177675559433697)),
      simde_mm256_set_epi64x(INT64_C( 6019682307676879898), INT64_C( -745177675559433697),
                             INT64_C( 6019682307676879898), INT64_C( -745177675559433697)) },
    { simde_mm_set_epi64x   (INT64_C(-8364368011425569946), INT64_C( 1685080214233190853)),
      simde_mm256_set_epi64x(INT64_C(-8364368011425569946), INT64_C( 1685080214233190853),
                             INT64_C(-8364368011425569946), INT64_C( 1685080214233190853)) },
    { simde_mm_set_epi64x   (INT64_C( 6712859087758853138), INT64_C( 2170550621944299043)),
      simde_mm256_set_epi64x(INT64_C( 6712859087758853138), INT64_C( 2170550621944299043),
                             INT64_C( 6712859087758853138), INT64_C( 2170550621944299043)) }
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_broadcastsi128_si256(test_vec[i].a);
    simde_assert_m256i_i64(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_cvtepi8_epi16(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m128i a;
    simde__m256i r;
  } test_vec[8] = {
    { simde_mm_set_epi8(INT8_C( -64), INT8_C( -39), INT8_C(  -1), INT8_C( 123),
                        INT8_C( -41), INT8_C(  42), INT8_C( -42), INT8_C(  48),
                        INT8_C(-101), INT8_C( -11), INT8_C(  78), INT8_C( -33),
                        INT8_C(  -4), INT8_C( -46), INT8_C(-128), INT8_C( 115)),
      simde_mm256_set_epi16(INT16_C(   -64), INT16_C(   -39), INT16_C(    -1), INT16_C(   123),
                            INT16_C(   -41), INT16_C(    42), INT16_C(   -42), INT16_C(    48),
                            INT16_C(  -101), INT16_C(   -11), INT16_C(    78), INT16_C(   -33),
                            INT16_C(    -4), INT16_C(   -46), INT16_C(  -128), INT16_C(   115)) },
    { simde_mm_set_epi8(INT8_C( -82), INT8_C(  92), INT8_C(  55), INT8_C( -41),
                        INT8_C(  61), INT8_C(-113), INT8_C( 108), INT8_C(  36),
                        INT8_C( 115), INT8_C(  53), INT8_C( -46), INT8_C( -96),
                        INT8_C( -71), INT8_C( -38), INT8_C(  25), INT8_C(  61)),
      simde_mm256_set_epi16(INT16_C(   -82), INT16_C(    92), INT16_C(    55), INT16_C(   -41),
                            INT16_C(    61), INT16_C(  -113), INT16_C(   108), INT16_C(    36),
                            INT16_C(   115), INT16_C(    53), INT16_C(   -46), INT16_C(   -96),
                            INT16_C(   -71), INT16_C(   -38), INT16_C(    25), INT16_C(    61)) },
    { simde_mm_set_epi8(INT8_C( -73), INT8_C(   5), INT8_C(  10), INT8_C(-111),
                        INT8_C(-127), INT8_C(  16), INT8_C( -16), INT8_C(-115),
                        INT8_C(  94), INT8_C(  88), INT8_C( -20), INT8_C( -24),
                        INT8_C( -27), INT8_C( -17), INT8_C( -31), INT8_C(  67)),
      simde_mm256_set_epi16(INT16_C(   -73), INT16_C(     5), INT16_C(    10), INT16_C(  -111),
                            INT16_C(  -127), INT16_C(    16), INT16_C(   -16), INT16_C(  -115),
                            INT16_C(    94), INT16_C(    88), INT16_C(   -20), INT16_C(   -24),
                            INT16_C(   -27), INT16_C(   -17), INT16_C(   -31), INT16_C(    67)) },
    { simde_mm_set_epi8(INT8_C( -17), INT8_C(   8), INT8_C(  67), INT8_C( -40),
                        INT8_C(  99), INT8_C(  89), INT8_C( -60), INT8_C( -24),
                        INT8_C( 120), INT8_C( -29), INT8_C(-127), INT8_C(  15),
                        INT8_C( -40), INT8_C(-106), INT8_C(  13), INT8_C( -27)),
      simde_mm256_set_epi16(INT16_C(   -17), INT16_C(     8), INT16_C(    67), INT16_C(   -40),
                            INT16_C(    99), INT16_C(    89), INT16_C(   -60), INT16_C(   -24),
                            INT16_C(   120), INT16_C(   -29), INT16_C(  -127), INT16_C(    15),
                            INT16_C(   -40), INT16_C(  -106), INT16_C(    13), INT16_C(   -27)) },
    { simde_mm_set_epi8(INT8_C(  -5), INT8_C(  52), INT8_C( 112), INT8_C( -86),
                        INT8_C(   7), INT8_C(   2), INT8_C(  89), INT8_C(  40),
                        INT8_C(  34), INT8_C( -14), INT8_C(-119), INT8_C(-115),
                        INT8_C(-103), INT8_C( 103), INT8_C( -15), INT8_C( -68)),
      simde_mm256_set_epi16(INT16_C(    -5), INT16_C(    52), INT16_C(   112), INT16_C(   -86),
                            INT16_C(     7), INT16_C(     2), INT16_C(    89), INT16_C(    40),
                            INT16_C(    34), INT16_C(   -14), INT16_C(  -119), INT16_C(  -115),
                            INT16_C(  -103), INT16_C(   103), INT16_C(   -15), INT16_C(   -68)) },
    { simde_mm_set_epi8(INT8_C(  34), INT8_C( 104), INT8_C(-116), INT8_C(-106),
                        INT8_C(-122), INT8_C(  51), INT8_C( -86), INT8_C(  26),
                        INT8_C(  57), INT8_C(  23), INT8_C( 125), INT8_C(  20),
                        INT8_C(  40), INT8_C( -87), INT8_C( -60), INT8_C( -93)),
      simde_mm256_set_epi16(INT16_C(    34), INT16_C(   104), INT16_C(  -116), INT16_C(  -106),
                            INT16_C(  -122), INT16_C(    51), INT16_C(   -86), INT16_C(    26),
                            INT16_C(    57), INT16_C(    23), INT16_C(   125), INT16_C(    20),
                            INT16_C(    40), INT16_C(   -87), INT16_C(   -60), INT16_C(   -93)) },
    { simde_mm_set_epi8(INT8_C(  35), INT8_C( 103), INT8_C(  83), INT8_C(  11),
                        INT8_C(   5), INT8_C( -26), INT8_C( -34), INT8_C( -28),
                        INT8_C( -15), INT8_C(  -2), INT8_C(  10), INT8_C( -97),
                        INT8_C(  35), INT8_C(-108), INT8_C(  38), INT8_C(-122)),
      simde_mm256_set_epi16(INT16_C(    35), INT16_C(   103), INT16_C(    83), INT16_C(    11),
                            INT16_C(     5), INT16_C(   -26), INT16_C(   -34), INT16_C(   -28),
                            INT16_C(   -15), INT16_C(    -2), INT16_C(    10), INT16_C(   -97),
                            INT16_C(    35), INT16_C(  -108), INT16_C(    38), INT16_C(  -122)) },
    { simde_mm_set_epi8(INT8_C(  44), INT8_C(-101), INT8_C(-122), INT8_C(  91),
                        INT8_C(  60), INT8_C(  60), INT8_C(  22), INT8_C(  81),
                        INT8_C(  13), INT8_C(-111), INT8_C(-125), INT8_C( -40),
                        INT8_C( -72), INT8_C(-102), INT8_C( -87), INT8_C( 108)),
      simde_mm256_set_epi16(INT16_C(    44), INT16_C(  -101), INT16_C(  -122), INT16_C(    91),
                            INT16_C(    60), INT16_C(    60), INT16_C(    22), INT16_C(    81),
                            INT16_C(    13), INT16_C(  -111), INT16_C(  -125), INT16_C(   -40),
                            INT16_C(   -72), INT16_C(  -102), INT16_C(   -87), INT16_C(   108)) },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_cvtepi8_epi16(test_vec[i].a);
    simde_assert_m256i_i16(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_cvtepi8_epi32(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m128i a;
    simde__m256i r;
  } test_vec[8] = {
    { simde_mm_set_epi8(INT8_C( 123), INT8_C(  -2), INT8_C( 102), INT8_C( -48),
                        INT8_C(  12), INT8_C(-119), INT8_C( -32), INT8_C(  68),
                        INT8_C( -88), INT8_C(  80), INT8_C(  32), INT8_C(-108),
                        INT8_C( -66), INT8_C(  35), INT8_C( -12), INT8_C(-103)),
      simde_mm256_set_epi32(INT32_C(        -88), INT32_C(         80), INT32_C(         32), INT32_C(       -108),
                            INT32_C(        -66), INT32_C(         35), INT32_C(        -12), INT32_C(       -103)) },
    { simde_mm_set_epi8(INT8_C( -12), INT8_C( -88), INT8_C( -20), INT8_C( -26),
                        INT8_C( -69), INT8_C( -40), INT8_C( 122), INT8_C(-121),
                        INT8_C(  47), INT8_C( 123), INT8_C( -15), INT8_C(-104),
                        INT8_C( -91), INT8_C( -13), INT8_C( -61), INT8_C(-104)),
      simde_mm256_set_epi32(INT32_C(         47), INT32_C(        123), INT32_C(        -15), INT32_C(       -104),
                            INT32_C(        -91), INT32_C(        -13), INT32_C(        -61), INT32_C(       -104)) },
    { simde_mm_set_epi8(INT8_C(-105), INT8_C(  35), INT8_C(-118), INT8_C( -44),
                        INT8_C( -91), INT8_C(  43), INT8_C(  18), INT8_C( -70),
                        INT8_C(  44), INT8_C(  98), INT8_C( -82), INT8_C(-126),
                        INT8_C( -80), INT8_C(-109), INT8_C(  69), INT8_C(-116)),
      simde_mm256_set_epi32(INT32_C(         44), INT32_C(         98), INT32_C(        -82), INT32_C(       -126),
                            INT32_C(        -80), INT32_C(       -109), INT32_C(         69), INT32_C(       -116)) },
    { simde_mm_set_epi8(INT8_C(  43), INT8_C(  92), INT8_C( -66), INT8_C( -32),
                        INT8_C(  71), INT8_C( -63), INT8_C(  51), INT8_C(  89),
                        INT8_C( 102), INT8_C(  -4), INT8_C( -28), INT8_C(  -5),
                        INT8_C(-107), INT8_C( -25), INT8_C(-107), INT8_C( -15)),
      simde_mm256_set_epi32(INT32_C(        102), INT32_C(         -4), INT32_C(        -28), INT32_C(         -5),
                            INT32_C(       -107), INT32_C(        -25), INT32_C(       -107), INT32_C(        -15)) },
    { simde_mm_set_epi8(INT8_C(  -7), INT8_C( -22), INT8_C(  -1), INT8_C(  29),
                        INT8_C(  -3), INT8_C( -97), INT8_C(  61), INT8_C( -36),
                        INT8_C( -81), INT8_C( -83), INT8_C(  54), INT8_C(  37),
                        INT8_C( -70), INT8_C( -70), INT8_C(  12), INT8_C( -61)),
      simde_mm256_set_epi32(INT32_C(        -81), INT32_C(        -83), INT32_C(         54), INT32_C(         37),
                            INT32_C(        -70), INT32_C(        -70), INT32_C(         12), INT32_C(        -61)) },
    { simde_mm_set_epi8(INT8_C(  88), INT8_C( -30), INT8_C( 125), INT8_C( -22),
                        INT8_C( -87), INT8_C(-109), INT8_C( -90), INT8_C( -86),
                        INT8_C(-124), INT8_C( -10), INT8_C(  57), INT8_C( -62),
                        INT8_C( -55), INT8_C(  40), INT8_C( -11), INT8_C(-100)),
      simde_mm256_set_epi32(INT32_C(       -124), INT32_C(        -10), INT32_C(         57), INT32_C(        -62),
                            INT32_C(        -55), INT32_C(         40), INT32_C(        -11), INT32_C(       -100)) },
    { simde_mm_set_epi8(INT8_C(  58), INT8_C(-110), INT8_C(  -6), INT8_C( -58),
                        INT8_C(-110), INT8_C( 125), INT8_C(  39), INT8_C( -82),
                        INT8_C( -88), INT8_C( 107), INT8_C(  76), INT8_C(  58),
                        INT8_C(  -2), INT8_C(-119), INT8_C( -27), INT8_C(  40)),
      simde_mm256_set_epi32(INT32_C(        -88), INT32_C(        107), INT32_C(         76), INT32_C(         58),
                            INT32_C(         -2), INT32_C(       -119), INT32_C(        -27), INT32_C(         40)) },
    { simde_mm_set_epi8(INT8_C(-110), INT8_C( -24), INT8_C( -33), INT8_C(-117),
                        INT8_C(  92), INT8_C( -35), INT8_C( 113), INT8_C(  13),
                        INT8_C(  46), INT8_C(-107), INT8_C(   4), INT8_C(   8),
                        INT8_C(  56), INT8_C(   9), INT8_C( 123), INT8_C(  36)),
      simde_mm256_set_epi32(INT32_C(         46), INT32_C(       -107), INT32_C(          4), INT32_C(          8),
                            INT32_C(         56), INT32_C(          9), INT32_C(        123), INT32_C(         36)) },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_cvtepi8_epi32(test_vec[i].a);
    simde_assert_m256i_i32(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_cvtepi8_epi64(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m128i a;
    simde__m256i r;
  } test_vec[8] = {
    { simde_mm_set_epi8(INT8_C(   9), INT8_C( -74), INT8_C( -52), INT8_C( -68),
                        INT8_C(  95), INT8_C( -10), INT8_C( -99), INT8_C( 121),
                        INT8_C(   1), INT8_C(  69), INT8_C( -36), INT8_C(-102),
                        INT8_C(-124), INT8_C( -93), INT8_C(-101), INT8_C(-118)),
      simde_mm256_set_epi64x(INT64_C(                -124), INT64_C(                 -93),
                             INT64_C(                -101), INT64_C(                -118)) },
    { simde_mm_set_epi8(INT8_C(-107), INT8_C( -34), INT8_C( -75), INT8_C( 119),
                        INT8_C( -79), INT8_C(-103), INT8_C(  -9), INT8_C(-121),
                        INT8_C( -51), INT8_C(   4), INT8_C(  89), INT8_C( 110),
                        INT8_C( 112), INT8_C(  67), INT8_C(-101), INT8_C(  87)),
      simde_mm256_set_epi64x(INT64_C(                 112), INT64_C(                  67),
                             INT64_C(                -101), INT64_C(                  87)) },
    { simde_mm_set_epi8(INT8_C( -85), INT8_C( 121), INT8_C(-116), INT8_C( 121),
                        INT8_C( -43), INT8_C( -80), INT8_C(   1), INT8_C(-102),
                        INT8_C(  39), INT8_C(-105), INT8_C( -26), INT8_C(  88),
                        INT8_C( -52), INT8_C(  61), INT8_C(-127), INT8_C(  21)),
      simde_mm256_set_epi64x(INT64_C(                 -52), INT64_C(                  61),
                             INT64_C(                -127), INT64_C(                  21)) },
    { simde_mm_set_epi8(INT8_C(  85), INT8_C(   1), INT8_C(  94), INT8_C(  60),
                        INT8_C( 102), INT8_C(   9), INT8_C( -56), INT8_C(  64),
                        INT8_C(-103), INT8_C( -86), INT8_C(  51), INT8_C(-126),
                        INT8_C(  -9), INT8_C(  88), INT8_C( -52), INT8_C(  13)),
      simde_mm256_set_epi64x(INT64_C(                  -9), INT64_C(                  88),
                             INT64_C(                 -52), INT64_C(                  13)) },
    { simde_mm_set_epi8(INT8_C(   0), INT8_C( -40), INT8_C(  42), INT8_C(  42),
                        INT8_C( 109), INT8_C(  -5), INT8_C( -28), INT8_C( -80),
                        INT8_C(  70), INT8_C(   6), INT8_C( -51), INT8_C(  17),
                        INT8_C(-105), INT8_C(-108), INT8_C(  14), INT8_C( -91)),
      simde_mm256_set_epi64x(INT64_C(                -105), INT64_C(                -108),
                             INT64_C(                  14), INT64_C(                 -91)) },
    { simde_mm_set_epi8(INT8_C( 125), INT8_C(-114), INT8_C( -39), INT8_C(-118),
                        INT8_C(  29), INT8_C( -81), INT8_C(-121), INT8_C( 115),
                        INT8_C(-128), INT8_C(  99), INT8_C(  64), INT8_C(   7),
                        INT8_C( 114), INT8_C(-101), INT8_C(-127), INT8_C(  30)),
      simde_mm256_set_epi64x(INT64_C(                 114), INT64_C(                -101),
                             INT64_C(                -127), INT64_C(                  30)) },
    { simde_mm_set_epi8(INT8_C(-126), INT8_C( 122), INT8_C(  50), INT8_C( 115),
                        INT8_C(  72), INT8_C( -56), INT8_C(  52), INT8_C( 125),
                        INT8_C(-104), INT8_C( -76), INT8_C(  65), INT8_C( 103),
                        INT8_C(-122), INT8_C( -36), INT8_C( -93), INT8_C( 110)),
      simde_mm256_set_epi64x(INT64_C(                -122), INT64_C(                 -36),
                             INT64_C(                 -93), INT64_C(                 110)) },
    { simde_mm_set_epi8(INT8_C( -80), INT8_C(  98), INT8_C(-119), INT8_C(  51),
                        INT8_C( -37), INT8_C( -17), INT8_C( -94), INT8_C(-122),
                        INT8_C(-114), INT8_C(  13), INT8_C( -75), INT8_C( 111),
                        INT8_C( -76), INT8_C( -15), INT8_C(  -1), INT8_C( -12)),
      simde_mm256_set_epi64x(INT64_C(                 -76), INT64_C(                 -15),
                             INT64_C(                  -1), INT64_C(                 -12)) },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_cvtepi8_epi64(test_vec[i].a);
    simde_assert_m256i_i64(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}


static MunitResult
test_simde_mm256_cvtepi16_epi32(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m128i a;
    simde__m256i r;
  } test_vec[8] = {
    { simde_mm_set_epi16(INT16_C( 29201), INT16_C( 17763), INT16_C( 13480), INT16_C( 29487),
                         INT16_C( -6581), INT16_C( 13446), INT16_C( 26538), INT16_C( -3936)),
      simde_mm256_set_epi32(INT32_C(      29201), INT32_C(      17763), INT32_C(      13480), INT32_C(      29487),
                            INT32_C(      -6581), INT32_C(      13446), INT32_C(      26538), INT32_C(      -3936)) },
    { simde_mm_set_epi16(INT16_C( -3829), INT16_C( 12503), INT16_C( 10513), INT16_C( 11407),
                         INT16_C( 28611), INT16_C(  5727), INT16_C( 32199), INT16_C( 11434)),
      simde_mm256_set_epi32(INT32_C(      -3829), INT32_C(      12503), INT32_C(      10513), INT32_C(      11407),
                            INT32_C(      28611), INT32_C(       5727), INT32_C(      32199), INT32_C(      11434)) },
    { simde_mm_set_epi16(INT16_C( -4989), INT16_C(-23450), INT16_C(-15441), INT16_C( 22895),
                         INT16_C(  2927), INT16_C(-20709), INT16_C( -7582), INT16_C(-31347)),
      simde_mm256_set_epi32(INT32_C(      -4989), INT32_C(     -23450), INT32_C(     -15441), INT32_C(      22895),
                            INT32_C(       2927), INT32_C(     -20709), INT32_C(      -7582), INT32_C(     -31347)) },
    { simde_mm_set_epi16(INT16_C( 24635), INT16_C( 21162), INT16_C( 29781), INT16_C(  -488),
                         INT16_C( -6580), INT16_C(-27732), INT16_C(   607), INT16_C(-20782)),
      simde_mm256_set_epi32(INT32_C(      24635), INT32_C(      21162), INT32_C(      29781), INT32_C(       -488),
                            INT32_C(      -6580), INT32_C(     -27732), INT32_C(        607), INT32_C(     -20782)) },
    { simde_mm_set_epi16(INT16_C(  -401), INT16_C( -5605), INT16_C(-28681), INT16_C(  4577),
                         INT16_C( -9094), INT16_C(  6804), INT16_C( -9223), INT16_C( 10661)),
      simde_mm256_set_epi32(INT32_C(       -401), INT32_C(      -5605), INT32_C(     -28681), INT32_C(       4577),
                            INT32_C(      -9094), INT32_C(       6804), INT32_C(      -9223), INT32_C(      10661)) },
    { simde_mm_set_epi16(INT16_C(  2053), INT16_C(-19489), INT16_C(  7360), INT16_C( 16515),
                         INT16_C( 32080), INT16_C(-16555), INT16_C(-32752), INT16_C( 19001)),
      simde_mm256_set_epi32(INT32_C(       2053), INT32_C(     -19489), INT32_C(       7360), INT32_C(      16515),
                            INT32_C(      32080), INT32_C(     -16555), INT32_C(     -32752), INT32_C(      19001)) },
    { simde_mm_set_epi16(INT16_C(-31610), INT16_C(-22910), INT16_C( 22850), INT16_C(-27168),
                         INT16_C( 13092), INT16_C(-21449), INT16_C( 16024), INT16_C(  8597)),
      simde_mm256_set_epi32(INT32_C(     -31610), INT32_C(     -22910), INT32_C(      22850), INT32_C(     -27168),
                            INT32_C(      13092), INT32_C(     -21449), INT32_C(      16024), INT32_C(       8597)) },
    { simde_mm_set_epi16(INT16_C( 28081), INT16_C( -7416), INT16_C( 18632), INT16_C(-28896),
                         INT16_C(-23156), INT16_C(-15424), INT16_C(-13082), INT16_C( 23555)),
      simde_mm256_set_epi32(INT32_C(      28081), INT32_C(      -7416), INT32_C(      18632), INT32_C(     -28896),
                            INT32_C(     -23156), INT32_C(     -15424), INT32_C(     -13082), INT32_C(      23555)) },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_cvtepi16_epi32(test_vec[i].a);
    simde_assert_m256i_i32(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_cvtepi16_epi64(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m128i a;
    simde__m256i r;
  } test_vec[8] = {
    { simde_mm_set_epi16(INT16_C(-31485), INT16_C(  6767), INT16_C( -1054), INT16_C(-15390),
                         INT16_C(-10897), INT16_C(-31336), INT16_C( -9551), INT16_C(  8617)),
      simde_mm256_set_epi64x(INT64_C(              -10897), INT64_C(              -31336),
                             INT64_C(               -9551), INT64_C(                8617)) },
    { simde_mm_set_epi16(INT16_C( 30988), INT16_C(  5181), INT16_C( 18938), INT16_C(-32273),
                         INT16_C(  5456), INT16_C( 19282), INT16_C(-21851), INT16_C( 27127)),
      simde_mm256_set_epi64x(INT64_C(                5456), INT64_C(               19282),
                             INT64_C(              -21851), INT64_C(               27127)) },
    { simde_mm_set_epi16(INT16_C( -7527), INT16_C(-20831), INT16_C( 23786), INT16_C(  3131),
                         INT16_C(-19886), INT16_C( -2045), INT16_C(-25062), INT16_C( -5779)),
      simde_mm256_set_epi64x(INT64_C(              -19886), INT64_C(               -2045),
                             INT64_C(              -25062), INT64_C(               -5779)) },
    { simde_mm_set_epi16(INT16_C( 31086), INT16_C( 22946), INT16_C( -1551), INT16_C(  9842),
                         INT16_C(-22586), INT16_C(  5015), INT16_C( 24465), INT16_C(-15199)),
      simde_mm256_set_epi64x(INT64_C(              -22586), INT64_C(                5015),
                             INT64_C(               24465), INT64_C(              -15199)) },
    { simde_mm_set_epi16(INT16_C( 20641), INT16_C(-16277), INT16_C( 32328), INT16_C( 21501),
                         INT16_C( 17537), INT16_C(-11745), INT16_C(-20371), INT16_C( 18200)),
      simde_mm256_set_epi64x(INT64_C(               17537), INT64_C(              -11745),
                             INT64_C(              -20371), INT64_C(               18200)) },
    { simde_mm_set_epi16(INT16_C(-26363), INT16_C(-18240), INT16_C( 21370), INT16_C(-23762),
                         INT16_C(  2610), INT16_C(  7301), INT16_C(-13295), INT16_C( 15532)),
      simde_mm256_set_epi64x(INT64_C(                2610), INT64_C(                7301),
                             INT64_C(              -13295), INT64_C(               15532)) },
    { simde_mm_set_epi16(INT16_C( -6112), INT16_C(-22921), INT16_C( -1544), INT16_C(-16225),
                         INT16_C( 14287), INT16_C(-23793), INT16_C(  5660), INT16_C(-22213)),
      simde_mm256_set_epi64x(INT64_C(               14287), INT64_C(              -23793),
                             INT64_C(                5660), INT64_C(              -22213)) },
    { simde_mm_set_epi16(INT16_C(  -130), INT16_C( -9648), INT16_C(-32446), INT16_C( 22661),
                         INT16_C( 18414), INT16_C(-28168), INT16_C( 10429), INT16_C(  9914)),
      simde_mm256_set_epi64x(INT64_C(               18414), INT64_C(              -28168),
                             INT64_C(               10429), INT64_C(                9914)) },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_cvtepi16_epi64(test_vec[i].a);
    simde_assert_m256i_i64(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_cvtepi32_epi64(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m128i a;
    simde__m256i r;
  } test_vec[8] = {
    { simde_mm_set_epi32(INT32_C( 1724176280), INT32_C( 1056866183), INT32_C(-1168814772), INT32_C(  436637329)),
      simde_mm256_set_epi32(INT32_C(          0), INT32_C( 1724176280), INT32_C(          0), INT32_C( 1056866183),
                            INT32_C(         -1), INT32_C(-1168814772), INT32_C(          0), INT32_C(  436637329)) },
    { simde_mm_set_epi32(INT32_C( -189342318), INT32_C( 1500351754), INT32_C(-1179088209), INT32_C(  373817664)),
      simde_mm256_set_epi32(INT32_C(         -1), INT32_C( -189342318), INT32_C(          0), INT32_C( 1500351754),
                            INT32_C(         -1), INT32_C(-1179088209), INT32_C(          0), INT32_C(  373817664)) },
    { simde_mm_set_epi32(INT32_C( -875273087), INT32_C(-1374882671), INT32_C(  170870738), INT32_C(  176375529)),
      simde_mm256_set_epi32(INT32_C(         -1), INT32_C( -875273087), INT32_C(         -1), INT32_C(-1374882671),
                            INT32_C(          0), INT32_C(  170870738), INT32_C(          0), INT32_C(  176375529)) },
    { simde_mm_set_epi32(INT32_C( 2051957746), INT32_C( -540720535), INT32_C( 2058375625), INT32_C(-1743932075)),
      simde_mm256_set_epi32(INT32_C(          0), INT32_C( 2051957746), INT32_C(         -1), INT32_C( -540720535),
                            INT32_C(          0), INT32_C( 2058375625), INT32_C(         -1), INT32_C(-1743932075)) },
    { simde_mm_set_epi32(INT32_C(   58481197), INT32_C(  -12810019), INT32_C(-1497428307), INT32_C(-1188147093)),
      simde_mm256_set_epi32(INT32_C(          0), INT32_C(   58481197), INT32_C(         -1), INT32_C(  -12810019),
                            INT32_C(         -1), INT32_C(-1497428307), INT32_C(         -1), INT32_C(-1188147093)) },
    { simde_mm_set_epi32(INT32_C( 2090870443), INT32_C( -917208135), INT32_C( 2079627861), INT32_C( -768384061)),
      simde_mm256_set_epi32(INT32_C(          0), INT32_C( 2090870443), INT32_C(         -1), INT32_C( -917208135),
                            INT32_C(          0), INT32_C( 2079627861), INT32_C(         -1), INT32_C( -768384061)) },
    { simde_mm_set_epi32(INT32_C( -297580502), INT32_C(-1417106854), INT32_C(-1288213555), INT32_C(    3240585)),
      simde_mm256_set_epi32(INT32_C(         -1), INT32_C( -297580502), INT32_C(         -1), INT32_C(-1417106854),
                            INT32_C(         -1), INT32_C(-1288213555), INT32_C(          0), INT32_C(    3240585)) },
    { simde_mm_set_epi32(INT32_C( 1692537538), INT32_C( -764623934), INT32_C( 1120288816), INT32_C(  296268349)),
      simde_mm256_set_epi32(INT32_C(          0), INT32_C( 1692537538), INT32_C(         -1), INT32_C( -764623934),
                            INT32_C(          0), INT32_C( 1120288816), INT32_C(          0), INT32_C(  296268349)) },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_cvtepi32_epi64(test_vec[i].a);
    simde_assert_m256i_i64(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_cvtepu8_epi16(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m128i a;
    simde__m256i r;
  } test_vec[8] = {
    { simde_x_mm_set_epu8(UINT8_C(240), UINT8_C( 50), UINT8_C(144), UINT8_C(  4),
                          UINT8_C(  7), UINT8_C(233), UINT8_C(157), UINT8_C( 74),
                          UINT8_C(217), UINT8_C( 90), UINT8_C(141), UINT8_C(254),
                          UINT8_C(115), UINT8_C( 96), UINT8_C(126), UINT8_C( 23)),
      simde_mm256_set_epi16(INT16_C(   240), INT16_C(    50), INT16_C(   144), INT16_C(     4),
                            INT16_C(     7), INT16_C(   233), INT16_C(   157), INT16_C(    74),
                            INT16_C(   217), INT16_C(    90), INT16_C(   141), INT16_C(   254),
                            INT16_C(   115), INT16_C(    96), INT16_C(   126), INT16_C(    23)) },
    { simde_x_mm_set_epu8(UINT8_C( 79), UINT8_C(126), UINT8_C(254), UINT8_C( 77),
                          UINT8_C(225), UINT8_C( 76), UINT8_C( 61), UINT8_C(223),
                          UINT8_C( 95), UINT8_C(244), UINT8_C( 66), UINT8_C(  4),
                          UINT8_C(241), UINT8_C(112), UINT8_C(120), UINT8_C(166)),
      simde_mm256_set_epi16(INT16_C(    79), INT16_C(   126), INT16_C(   254), INT16_C(    77),
                            INT16_C(   225), INT16_C(    76), INT16_C(    61), INT16_C(   223),
                            INT16_C(    95), INT16_C(   244), INT16_C(    66), INT16_C(     4),
                            INT16_C(   241), INT16_C(   112), INT16_C(   120), INT16_C(   166)) },
    { simde_x_mm_set_epu8(UINT8_C( 56), UINT8_C(107), UINT8_C(114), UINT8_C( 86),
                          UINT8_C( 35), UINT8_C( 47), UINT8_C( 25), UINT8_C(187),
                          UINT8_C(176), UINT8_C( 49), UINT8_C(164), UINT8_C(236),
                          UINT8_C(110), UINT8_C( 61), UINT8_C( 64), UINT8_C( 42)),
      simde_mm256_set_epi16(INT16_C(    56), INT16_C(   107), INT16_C(   114), INT16_C(    86),
                            INT16_C(    35), INT16_C(    47), INT16_C(    25), INT16_C(   187),
                            INT16_C(   176), INT16_C(    49), INT16_C(   164), INT16_C(   236),
                            INT16_C(   110), INT16_C(    61), INT16_C(    64), INT16_C(    42)) },
    { simde_x_mm_set_epu8(UINT8_C( 54), UINT8_C(130), UINT8_C(171), UINT8_C( 76),
                          UINT8_C( 75), UINT8_C(192), UINT8_C(152), UINT8_C(247),
                          UINT8_C(165), UINT8_C(252), UINT8_C(115), UINT8_C( 73),
                          UINT8_C( 86), UINT8_C( 52), UINT8_C( 29), UINT8_C(227)),
      simde_mm256_set_epi16(INT16_C(    54), INT16_C(   130), INT16_C(   171), INT16_C(    76),
                            INT16_C(    75), INT16_C(   192), INT16_C(   152), INT16_C(   247),
                            INT16_C(   165), INT16_C(   252), INT16_C(   115), INT16_C(    73),
                            INT16_C(    86), INT16_C(    52), INT16_C(    29), INT16_C(   227)) },
    { simde_x_mm_set_epu8(UINT8_C(175), UINT8_C(214), UINT8_C(138), UINT8_C(132),
                          UINT8_C( 59), UINT8_C( 53), UINT8_C(175), UINT8_C( 98),
                          UINT8_C(195), UINT8_C(230), UINT8_C(207), UINT8_C(189),
                          UINT8_C(100), UINT8_C(255), UINT8_C( 84), UINT8_C(129)),
      simde_mm256_set_epi16(INT16_C(   175), INT16_C(   214), INT16_C(   138), INT16_C(   132),
                            INT16_C(    59), INT16_C(    53), INT16_C(   175), INT16_C(    98),
                            INT16_C(   195), INT16_C(   230), INT16_C(   207), INT16_C(   189),
                            INT16_C(   100), INT16_C(   255), INT16_C(    84), INT16_C(   129)) },
    { simde_x_mm_set_epu8(UINT8_C( 40), UINT8_C( 10), UINT8_C(243), UINT8_C( 28),
                          UINT8_C( 48), UINT8_C(231), UINT8_C(240), UINT8_C(  2),
                          UINT8_C(  1), UINT8_C( 20), UINT8_C(184), UINT8_C(244),
                          UINT8_C(174), UINT8_C(138), UINT8_C( 47), UINT8_C(122)),
      simde_mm256_set_epi16(INT16_C(    40), INT16_C(    10), INT16_C(   243), INT16_C(    28),
                            INT16_C(    48), INT16_C(   231), INT16_C(   240), INT16_C(     2),
                            INT16_C(     1), INT16_C(    20), INT16_C(   184), INT16_C(   244),
                            INT16_C(   174), INT16_C(   138), INT16_C(    47), INT16_C(   122)) },
    { simde_x_mm_set_epu8(UINT8_C( 90), UINT8_C(144), UINT8_C(116), UINT8_C( 64),
                          UINT8_C(250), UINT8_C(233), UINT8_C(185), UINT8_C(193),
                          UINT8_C(172), UINT8_C(128), UINT8_C( 92), UINT8_C(230),
                          UINT8_C(153), UINT8_C( 17), UINT8_C(  8), UINT8_C(121)),
      simde_mm256_set_epi16(INT16_C(    90), INT16_C(   144), INT16_C(   116), INT16_C(    64),
                            INT16_C(   250), INT16_C(   233), INT16_C(   185), INT16_C(   193),
                            INT16_C(   172), INT16_C(   128), INT16_C(    92), INT16_C(   230),
                            INT16_C(   153), INT16_C(    17), INT16_C(     8), INT16_C(   121)) },
    { simde_x_mm_set_epu8(UINT8_C(135), UINT8_C(132), UINT8_C(184), UINT8_C(244),
                          UINT8_C(164), UINT8_C( 94), UINT8_C(216), UINT8_C(238),
                          UINT8_C(112), UINT8_C(252), UINT8_C( 78), UINT8_C(150),
                          UINT8_C( 72), UINT8_C(215), UINT8_C(214), UINT8_C(215)),
      simde_mm256_set_epi16(INT16_C(   135), INT16_C(   132), INT16_C(   184), INT16_C(   244),
                            INT16_C(   164), INT16_C(    94), INT16_C(   216), INT16_C(   238),
                            INT16_C(   112), INT16_C(   252), INT16_C(    78), INT16_C(   150),
                            INT16_C(    72), INT16_C(   215), INT16_C(   214), INT16_C(   215)) },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_cvtepu8_epi16(test_vec[i].a);
    simde_assert_m256i_i16(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_cvtepu8_epi32(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m128i a;
    simde__m256i r;
  } test_vec[8] = {
    { simde_x_mm_set_epu8(UINT8_C(240), UINT8_C( 50), UINT8_C(144), UINT8_C(  4),
                          UINT8_C(  7), UINT8_C(233), UINT8_C(157), UINT8_C( 74),
                          UINT8_C(217), UINT8_C( 90), UINT8_C(141), UINT8_C(254),
                          UINT8_C(115), UINT8_C( 96), UINT8_C(126), UINT8_C( 23)),
      simde_mm256_set_epi32(INT32_C(        217), INT32_C(         90), INT32_C(        141), INT32_C(        254),
                            INT32_C(        115), INT32_C(         96), INT32_C(        126), INT32_C(         23)) },
    { simde_x_mm_set_epu8(UINT8_C( 79), UINT8_C(126), UINT8_C(254), UINT8_C( 77),
                          UINT8_C(225), UINT8_C( 76), UINT8_C( 61), UINT8_C(223),
                          UINT8_C( 95), UINT8_C(244), UINT8_C( 66), UINT8_C(  4),
                          UINT8_C(241), UINT8_C(112), UINT8_C(120), UINT8_C(166)),
      simde_mm256_set_epi32(INT32_C(         95), INT32_C(        244), INT32_C(         66), INT32_C(          4),
                            INT32_C(        241), INT32_C(        112), INT32_C(        120), INT32_C(        166)) },
    { simde_x_mm_set_epu8(UINT8_C( 56), UINT8_C(107), UINT8_C(114), UINT8_C( 86),
                          UINT8_C( 35), UINT8_C( 47), UINT8_C( 25), UINT8_C(187),
                          UINT8_C(176), UINT8_C( 49), UINT8_C(164), UINT8_C(236),
                          UINT8_C(110), UINT8_C( 61), UINT8_C( 64), UINT8_C( 42)),
      simde_mm256_set_epi32(INT32_C(        176), INT32_C(         49), INT32_C(        164), INT32_C(        236),
                            INT32_C(        110), INT32_C(         61), INT32_C(         64), INT32_C(         42)) },
    { simde_x_mm_set_epu8(UINT8_C( 54), UINT8_C(130), UINT8_C(171), UINT8_C( 76),
                          UINT8_C( 75), UINT8_C(192), UINT8_C(152), UINT8_C(247),
                          UINT8_C(165), UINT8_C(252), UINT8_C(115), UINT8_C( 73),
                          UINT8_C( 86), UINT8_C( 52), UINT8_C( 29), UINT8_C(227)),
      simde_mm256_set_epi32(INT32_C(        165), INT32_C(        252), INT32_C(        115), INT32_C(         73),
                            INT32_C(         86), INT32_C(         52), INT32_C(         29), INT32_C(        227)) },
    { simde_x_mm_set_epu8(UINT8_C(175), UINT8_C(214), UINT8_C(138), UINT8_C(132),
                          UINT8_C( 59), UINT8_C( 53), UINT8_C(175), UINT8_C( 98),
                          UINT8_C(195), UINT8_C(230), UINT8_C(207), UINT8_C(189),
                          UINT8_C(100), UINT8_C(255), UINT8_C( 84), UINT8_C(129)),
      simde_mm256_set_epi32(INT32_C(        195), INT32_C(        230), INT32_C(        207), INT32_C(        189),
                            INT32_C(        100), INT32_C(        255), INT32_C(         84), INT32_C(        129)) },
    { simde_x_mm_set_epu8(UINT8_C( 40), UINT8_C( 10), UINT8_C(243), UINT8_C( 28),
                          UINT8_C( 48), UINT8_C(231), UINT8_C(240), UINT8_C(  2),
                          UINT8_C(  1), UINT8_C( 20), UINT8_C(184), UINT8_C(244),
                          UINT8_C(174), UINT8_C(138), UINT8_C( 47), UINT8_C(122)),
      simde_mm256_set_epi32(INT32_C(          1), INT32_C(         20), INT32_C(        184), INT32_C(        244),
                            INT32_C(        174), INT32_C(        138), INT32_C(         47), INT32_C(        122)) },
    { simde_x_mm_set_epu8(UINT8_C( 90), UINT8_C(144), UINT8_C(116), UINT8_C( 64),
                          UINT8_C(250), UINT8_C(233), UINT8_C(185), UINT8_C(193),
                          UINT8_C(172), UINT8_C(128), UINT8_C( 92), UINT8_C(230),
                          UINT8_C(153), UINT8_C( 17), UINT8_C(  8), UINT8_C(121)),
      simde_mm256_set_epi32(INT32_C(        172), INT32_C(        128), INT32_C(         92), INT32_C(        230),
                            INT32_C(        153), INT32_C(         17), INT32_C(          8), INT32_C(        121)) },
    { simde_x_mm_set_epu8(UINT8_C(135), UINT8_C(132), UINT8_C(184), UINT8_C(244),
                          UINT8_C(164), UINT8_C( 94), UINT8_C(216), UINT8_C(238),
                          UINT8_C(112), UINT8_C(252), UINT8_C( 78), UINT8_C(150),
                          UINT8_C( 72), UINT8_C(215), UINT8_C(214), UINT8_C(215)),
      simde_mm256_set_epi32(INT32_C(        112), INT32_C(        252), INT32_C(         78), INT32_C(        150),
                            INT32_C(         72), INT32_C(        215), INT32_C(        214), INT32_C(        215)) },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_cvtepu8_epi32(test_vec[i].a);
    simde_assert_m256i_i32(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_cvtepu8_epi64(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m128i a;
    simde__m256i r;
  } test_vec[8] = {
    { simde_x_mm_set_epu8(UINT8_C(  9), UINT8_C(182), UINT8_C(204), UINT8_C(188),
                          UINT8_C( 95), UINT8_C(246), UINT8_C(157), UINT8_C(121),
                          UINT8_C(  1), UINT8_C( 69), UINT8_C(220), UINT8_C(154),
                          UINT8_C(132), UINT8_C(163), UINT8_C(155), UINT8_C(138)),
      simde_mm256_set_epi64x(INT64_C(                 132), INT64_C(                 163),
                             INT64_C(                 155), INT64_C(                 138)) },
    { simde_x_mm_set_epu8(UINT8_C(149), UINT8_C(222), UINT8_C(181), UINT8_C(119),
                          UINT8_C(177), UINT8_C(153), UINT8_C(247), UINT8_C(135),
                          UINT8_C(205), UINT8_C(  4), UINT8_C( 89), UINT8_C(110),
                          UINT8_C(112), UINT8_C( 67), UINT8_C(155), UINT8_C( 87)),
      simde_mm256_set_epi64x(INT64_C(                 112), INT64_C(                  67),
                             INT64_C(                 155), INT64_C(                  87)) },
    { simde_x_mm_set_epu8(UINT8_C(171), UINT8_C(121), UINT8_C(140), UINT8_C(121),
                          UINT8_C(213), UINT8_C(176), UINT8_C(  1), UINT8_C(154),
                          UINT8_C( 39), UINT8_C(151), UINT8_C(230), UINT8_C( 88),
                          UINT8_C(204), UINT8_C( 61), UINT8_C(129), UINT8_C( 21)),
      simde_mm256_set_epi64x(INT64_C(                 204), INT64_C(                  61),
                             INT64_C(                 129), INT64_C(                  21)) },
    { simde_x_mm_set_epu8(UINT8_C( 85), UINT8_C(  1), UINT8_C( 94), UINT8_C( 60),
                          UINT8_C(102), UINT8_C(  9), UINT8_C(200), UINT8_C( 64),
                          UINT8_C(153), UINT8_C(170), UINT8_C( 51), UINT8_C(130),
                          UINT8_C(247), UINT8_C( 88), UINT8_C(204), UINT8_C( 13)),
      simde_mm256_set_epi64x(INT64_C(                 247), INT64_C(                  88),
                             INT64_C(                 204), INT64_C(                  13)) },
    { simde_x_mm_set_epu8(UINT8_C(  0), UINT8_C(216), UINT8_C( 42), UINT8_C( 42),
                          UINT8_C(109), UINT8_C(251), UINT8_C(228), UINT8_C(176),
                          UINT8_C( 70), UINT8_C(  6), UINT8_C(205), UINT8_C( 17),
                          UINT8_C(151), UINT8_C(148), UINT8_C( 14), UINT8_C(165)),
      simde_mm256_set_epi64x(INT64_C(                 151), INT64_C(                 148),
                             INT64_C(                  14), INT64_C(                 165)) },
    { simde_x_mm_set_epu8(UINT8_C(125), UINT8_C(142), UINT8_C(217), UINT8_C(138),
                          UINT8_C( 29), UINT8_C(175), UINT8_C(135), UINT8_C(115),
                          UINT8_C(128), UINT8_C( 99), UINT8_C( 64), UINT8_C(  7),
                          UINT8_C(114), UINT8_C(155), UINT8_C(129), UINT8_C( 30)),
      simde_mm256_set_epi64x(INT64_C(                 114), INT64_C(                 155),
                             INT64_C(                 129), INT64_C(                  30)) },
    { simde_x_mm_set_epu8(UINT8_C(130), UINT8_C(122), UINT8_C( 50), UINT8_C(115),
                          UINT8_C( 72), UINT8_C(200), UINT8_C( 52), UINT8_C(125),
                          UINT8_C(152), UINT8_C(180), UINT8_C( 65), UINT8_C(103),
                          UINT8_C(134), UINT8_C(220), UINT8_C(163), UINT8_C(110)),
      simde_mm256_set_epi64x(INT64_C(                 134), INT64_C(                 220),
                             INT64_C(                 163), INT64_C(                 110)) },
    { simde_x_mm_set_epu8(UINT8_C(176), UINT8_C( 98), UINT8_C(137), UINT8_C( 51),
                          UINT8_C(219), UINT8_C(239), UINT8_C(162), UINT8_C(134),
                          UINT8_C(142), UINT8_C( 13), UINT8_C(181), UINT8_C(111),
                          UINT8_C(180), UINT8_C(241), UINT8_C(255), UINT8_C(244)),
      simde_mm256_set_epi64x(INT64_C(                 180), INT64_C(                 241),
                             INT64_C(                 255), INT64_C(                 244)) },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_cvtepu8_epi64(test_vec[i].a);
    simde_assert_m256i_i64(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_cvtepu16_epi32(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m128i a;
    simde__m256i r;
  } test_vec[8] = {
    { simde_x_mm_set_epu16(UINT16_C(61490), UINT16_C(36868), UINT16_C( 2025), UINT16_C(40266),
                           UINT16_C(55642), UINT16_C(36350), UINT16_C(29536), UINT16_C(32279)),
      simde_mm256_set_epi32(INT32_C(      61490), INT32_C(      36868), INT32_C(       2025), INT32_C(      40266),
                            INT32_C(      55642), INT32_C(      36350), INT32_C(      29536), INT32_C(      32279)) },
    { simde_x_mm_set_epu16(UINT16_C(20350), UINT16_C(65101), UINT16_C(57676), UINT16_C(15839),
                           UINT16_C(24564), UINT16_C(16900), UINT16_C(61808), UINT16_C(30886)),
      simde_mm256_set_epi32(INT32_C(      20350), INT32_C(      65101), INT32_C(      57676), INT32_C(      15839),
                            INT32_C(      24564), INT32_C(      16900), INT32_C(      61808), INT32_C(      30886)) },
    { simde_x_mm_set_epu16(UINT16_C(14443), UINT16_C(29270), UINT16_C( 9007), UINT16_C( 6587),
                           UINT16_C(45105), UINT16_C(42220), UINT16_C(28221), UINT16_C(16426)),
      simde_mm256_set_epi32(INT32_C(      14443), INT32_C(      29270), INT32_C(       9007), INT32_C(       6587),
                            INT32_C(      45105), INT32_C(      42220), INT32_C(      28221), INT32_C(      16426)) },
    { simde_x_mm_set_epu16(UINT16_C(13954), UINT16_C(43852), UINT16_C(19392), UINT16_C(39159),
                           UINT16_C(42492), UINT16_C(29513), UINT16_C(22068), UINT16_C( 7651)),
      simde_mm256_set_epi32(INT32_C(      13954), INT32_C(      43852), INT32_C(      19392), INT32_C(      39159),
                            INT32_C(      42492), INT32_C(      29513), INT32_C(      22068), INT32_C(       7651)) },
    { simde_x_mm_set_epu16(UINT16_C(45014), UINT16_C(35460), UINT16_C(15157), UINT16_C(44898),
                           UINT16_C(50150), UINT16_C(53181), UINT16_C(25855), UINT16_C(21633)),
      simde_mm256_set_epi32(INT32_C(      45014), INT32_C(      35460), INT32_C(      15157), INT32_C(      44898),
                            INT32_C(      50150), INT32_C(      53181), INT32_C(      25855), INT32_C(      21633)) },
    { simde_x_mm_set_epu16(UINT16_C(10250), UINT16_C(62236), UINT16_C(12519), UINT16_C(61442),
                           UINT16_C(  276), UINT16_C(47348), UINT16_C(44682), UINT16_C(12154)),
      simde_mm256_set_epi32(INT32_C(      10250), INT32_C(      62236), INT32_C(      12519), INT32_C(      61442),
                            INT32_C(        276), INT32_C(      47348), INT32_C(      44682), INT32_C(      12154)) },
    { simde_x_mm_set_epu16(UINT16_C(23184), UINT16_C(29760), UINT16_C(64233), UINT16_C(47553),
                           UINT16_C(44160), UINT16_C(23782), UINT16_C(39185), UINT16_C( 2169)),
      simde_mm256_set_epi32(INT32_C(      23184), INT32_C(      29760), INT32_C(      64233), INT32_C(      47553),
                            INT32_C(      44160), INT32_C(      23782), INT32_C(      39185), INT32_C(       2169)) },
    { simde_x_mm_set_epu16(UINT16_C(34692), UINT16_C(47348), UINT16_C(42078), UINT16_C(55534),
                           UINT16_C(28924), UINT16_C(20118), UINT16_C(18647), UINT16_C(54999)),
      simde_mm256_set_epi32(INT32_C(      34692), INT32_C(      47348), INT32_C(      42078), INT32_C(      55534),
                            INT32_C(      28924), INT32_C(      20118), INT32_C(      18647), INT32_C(      54999)) },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_cvtepu16_epi32(test_vec[i].a);
    simde_assert_m256i_i32(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_cvtepu16_epi64(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m128i a;
    simde__m256i r;
  } test_vec[8] = {
    { simde_x_mm_set_epu16(UINT16_C(61490), UINT16_C(36868), UINT16_C( 2025), UINT16_C(40266),
                           UINT16_C(55642), UINT16_C(36350), UINT16_C(29536), UINT16_C(32279)),
      simde_mm256_set_epi64x(INT64_C(               55642), INT64_C(               36350),
                             INT64_C(               29536), INT64_C(               32279)) },
    { simde_x_mm_set_epu16(UINT16_C(20350), UINT16_C(65101), UINT16_C(57676), UINT16_C(15839),
                           UINT16_C(24564), UINT16_C(16900), UINT16_C(61808), UINT16_C(30886)),
      simde_mm256_set_epi64x(INT64_C(               24564), INT64_C(               16900),
                             INT64_C(               61808), INT64_C(               30886)) },
    { simde_x_mm_set_epu16(UINT16_C(14443), UINT16_C(29270), UINT16_C( 9007), UINT16_C( 6587),
                           UINT16_C(45105), UINT16_C(42220), UINT16_C(28221), UINT16_C(16426)),
      simde_mm256_set_epi64x(INT64_C(               45105), INT64_C(               42220),
                             INT64_C(               28221), INT64_C(               16426)) },
    { simde_x_mm_set_epu16(UINT16_C(13954), UINT16_C(43852), UINT16_C(19392), UINT16_C(39159),
                           UINT16_C(42492), UINT16_C(29513), UINT16_C(22068), UINT16_C( 7651)),
      simde_mm256_set_epi64x(INT64_C(               42492), INT64_C(               29513),
                             INT64_C(               22068), INT64_C(                7651)) },
    { simde_x_mm_set_epu16(UINT16_C(45014), UINT16_C(35460), UINT16_C(15157), UINT16_C(44898),
                           UINT16_C(50150), UINT16_C(53181), UINT16_C(25855), UINT16_C(21633)),
      simde_mm256_set_epi64x(INT64_C(               50150), INT64_C(               53181),
                             INT64_C(               25855), INT64_C(               21633)) },
    { simde_x_mm_set_epu16(UINT16_C(10250), UINT16_C(62236), UINT16_C(12519), UINT16_C(61442),
                           UINT16_C(  276), UINT16_C(47348), UINT16_C(44682), UINT16_C(12154)),
      simde_mm256_set_epi64x(INT64_C(                 276), INT64_C(               47348),
                             INT64_C(               44682), INT64_C(               12154)) },
    { simde_x_mm_set_epu16(UINT16_C(23184), UINT16_C(29760), UINT16_C(64233), UINT16_C(47553),
                           UINT16_C(44160), UINT16_C(23782), UINT16_C(39185), UINT16_C( 2169)),
      simde_mm256_set_epi64x(INT64_C(               44160), INT64_C(               23782),
                             INT64_C(               39185), INT64_C(                2169)) },
    { simde_x_mm_set_epu16(UINT16_C(34692), UINT16_C(47348), UINT16_C(42078), UINT16_C(55534),
                           UINT16_C(28924), UINT16_C(20118), UINT16_C(18647), UINT16_C(54999)),
      simde_mm256_set_epi64x(INT64_C(               28924), INT64_C(               20118),
                             INT64_C(               18647), INT64_C(               54999)) },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_cvtepu16_epi64(test_vec[i].a);
    simde_assert_m256i_i64(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_cvtepu32_epi64(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m128i a;
    simde__m256i r;
  } test_vec[8] = {
    { simde_x_mm_set_epu32(UINT32_C(2027668512), UINT32_C(4262540660), UINT32_C(2279720356), UINT32_C( 579063940)),
      simde_mm256_set_epi64x(INT64_C(          2027668512), INT64_C(          4262540660),
                             INT64_C(          2279720356), INT64_C(           579063940)) },
    { simde_x_mm_set_epu32(UINT32_C( 214101781), UINT32_C(2515026933), UINT32_C(  10021235), UINT32_C(4284419101)),
      simde_mm256_set_epi64x(INT64_C(           214101781), INT64_C(          2515026933),
                             INT64_C(            10021235), INT64_C(          4284419101)) },
    { simde_x_mm_set_epu32(UINT32_C(2492492584), UINT32_C(1475674737), UINT32_C( 145233694), UINT32_C(2838555915)),
      simde_mm256_set_epi64x(INT64_C(          2492492584), INT64_C(          1475674737),
                             INT64_C(           145233694), INT64_C(          2838555915)) },
    { simde_x_mm_set_epu32(UINT32_C(3488754722), UINT32_C(2142666247), UINT32_C(4044693026), UINT32_C( 975481583)),
      simde_mm256_set_epi64x(INT64_C(          3488754722), INT64_C(          2142666247),
                             INT64_C(          4044693026), INT64_C(           975481583)) },
    { simde_x_mm_set_epu32(UINT32_C(3942926803), UINT32_C(  10053147), UINT32_C(3324554936), UINT32_C( 275092283)),
      simde_mm256_set_epi64x(INT64_C(          3942926803), INT64_C(            10053147),
                             INT64_C(          3324554936), INT64_C(           275092283)) },
    { simde_x_mm_set_epu32(UINT32_C( 609927901), UINT32_C(4032952140), UINT32_C(2163741382), UINT32_C(1197307836)),
      simde_mm256_set_epi64x(INT64_C(           609927901), INT64_C(          4032952140),
                             INT64_C(          2163741382), INT64_C(          1197307836)) },
    { simde_x_mm_set_epu32(UINT32_C( 667494753), UINT32_C(  25338810), UINT32_C( 229628292), UINT32_C(1413771580)),
      simde_mm256_set_epi64x(INT64_C(           667494753), INT64_C(            25338810),
                             INT64_C(           229628292), INT64_C(          1413771580)) },
    { simde_x_mm_set_epu32(UINT32_C(3461166204), UINT32_C(2882591041), UINT32_C(4038947223), UINT32_C(3672325978)),
      simde_mm256_set_epi64x(INT64_C(          3461166204), INT64_C(          2882591041),
                             INT64_C(          4038947223), INT64_C(          3672325978)) },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_cvtepu32_epi64(test_vec[i].a);
    simde_assert_m256i_i64(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_extract_epi8(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m256i a;
    int index;
    int r;
  } test_vec[8] = {
    { simde_mm256_set_epi8(INT8_C(  85), INT8_C(-106), INT8_C(  44), INT8_C( -49),
                           INT8_C( 119), INT8_C(  80), INT8_C( 116), INT8_C( -43),
                           INT8_C( -47), INT8_C( -11), INT8_C(  62), INT8_C( -51),
                           INT8_C( -20), INT8_C( -60), INT8_C(-115), INT8_C(   4),
                           INT8_C( 127), INT8_C( -43), INT8_C( -71), INT8_C(  56),
                           INT8_C( -31), INT8_C(  66), INT8_C(  34), INT8_C(-119),
                           INT8_C(  19), INT8_C(  36), INT8_C( -12), INT8_C( 112),
                           INT8_C(  60), INT8_C(  83), INT8_C(-120), INT8_C(  56)),
      31, 85 },
    { simde_mm256_set_epi8(INT8_C(  18), INT8_C(  -1), INT8_C(  58), INT8_C(  88),
                           INT8_C( 126), INT8_C(  33), INT8_C( -76), INT8_C(  89),
                           INT8_C( 117), INT8_C(  96), INT8_C(  36), INT8_C( -36),
                           INT8_C( 119), INT8_C(  42), INT8_C(  42), INT8_C(  20),
                           INT8_C(  29), INT8_C(  56), INT8_C(  62), INT8_C(  24),
                           INT8_C( 114), INT8_C(  -2), INT8_C(  32), INT8_C( -56),
                           INT8_C( -33), INT8_C( -80), INT8_C( 116), INT8_C(  62),
                           INT8_C( -70), INT8_C( -24), INT8_C( 104), INT8_C( 113)),
      2, -24 },
    { simde_mm256_set_epi8(INT8_C( 126), INT8_C(-115), INT8_C(-111), INT8_C( 126),
                           INT8_C(  64), INT8_C(  84), INT8_C(-101), INT8_C( -21),
                           INT8_C(  63), INT8_C( -34), INT8_C( -47), INT8_C( 123),
                           INT8_C(  67), INT8_C( -48), INT8_C( -40), INT8_C( -10),
                           INT8_C( -48), INT8_C(-117), INT8_C( 115), INT8_C( -29),
                           INT8_C(  -9), INT8_C(  82), INT8_C(  65), INT8_C(  40),
                           INT8_C(   0), INT8_C(  84), INT8_C(  65), INT8_C( -33),
                           INT8_C( 106), INT8_C(  47), INT8_C( -38), INT8_C(  57)),
      12, -29 },
    { simde_mm256_set_epi8(INT8_C(  -5), INT8_C(-104), INT8_C(  70), INT8_C( 103),
                           INT8_C(  37), INT8_C( -19), INT8_C(  55), INT8_C(  18),
                           INT8_C(  29), INT8_C( -66), INT8_C(-109), INT8_C(-128),
                           INT8_C(  94), INT8_C( -29), INT8_C( -29), INT8_C( -32),
                           INT8_C( -43), INT8_C(  55), INT8_C(  69), INT8_C( -62),
                           INT8_C( -91), INT8_C( -92), INT8_C(  80), INT8_C( -28),
                           INT8_C( -29), INT8_C( -53), INT8_C(-109), INT8_C( -97),
                           INT8_C(  13), INT8_C( -90), INT8_C( -67), INT8_C( -51)),
      29, 70 },
    { simde_mm256_set_epi8(INT8_C(  92), INT8_C(  10), INT8_C( 114), INT8_C( -32),
                           INT8_C(-114), INT8_C( -95), INT8_C( -42), INT8_C(  32),
                           INT8_C( -76), INT8_C( 127), INT8_C(  62), INT8_C(  11),
                           INT8_C( 127), INT8_C(  98), INT8_C(   5), INT8_C( -14),
                           INT8_C( -11), INT8_C( -28), INT8_C(-127), INT8_C(  51),
                           INT8_C( -66), INT8_C(  94), INT8_C(  -6), INT8_C(   7),
                           INT8_C( -95), INT8_C( -38), INT8_C(  -3), INT8_C(-103),
                           INT8_C( -87), INT8_C( 100), INT8_C(-113), INT8_C(  87)),
      22, 127 },
    { simde_mm256_set_epi8(INT8_C( -54), INT8_C(  70), INT8_C( 120), INT8_C( -67),
                           INT8_C(  17), INT8_C(  73), INT8_C(  40), INT8_C(-111),
                           INT8_C( 115), INT8_C( -79), INT8_C( -43), INT8_C(-120),
                           INT8_C(  70), INT8_C(  68), INT8_C( -87), INT8_C( -94),
                           INT8_C( 122), INT8_C( -19), INT8_C(-114), INT8_C(  82),
                           INT8_C(  81), INT8_C(  36), INT8_C(  42), INT8_C(-128),
                           INT8_C(  -8), INT8_C(  49), INT8_C( -14), INT8_C( -85),
                           INT8_C( -12), INT8_C( -81), INT8_C(  99), INT8_C(  11)),
      15, 122 },
    { simde_mm256_set_epi8(INT8_C(  27), INT8_C(  67), INT8_C( -85), INT8_C( -45),
                           INT8_C(-107), INT8_C(  17), INT8_C( -93), INT8_C( -57),
                           INT8_C(-113), INT8_C( -70), INT8_C(  37), INT8_C(  35),
                           INT8_C( -58), INT8_C(-116), INT8_C(  52), INT8_C( -81),
                           INT8_C( -49), INT8_C( -86), INT8_C( -44), INT8_C(  70),
                           INT8_C(  40), INT8_C(  67), INT8_C(  17), INT8_C( -49),
                           INT8_C(-118), INT8_C( -65), INT8_C(  29), INT8_C( -74),
                           INT8_C(   2), INT8_C(-103), INT8_C(  55), INT8_C(-109)),
      19, -58 },
    { simde_mm256_set_epi8(INT8_C( 104), INT8_C(  -9), INT8_C( 103), INT8_C( -86),
                           INT8_C(   0), INT8_C(  11), INT8_C(-114), INT8_C( -78),
                           INT8_C(-128), INT8_C(  29), INT8_C(  27), INT8_C(-121),
                           INT8_C( -68), INT8_C(   9), INT8_C(   6), INT8_C( 111),
                           INT8_C(-117), INT8_C(  82), INT8_C(  75), INT8_C(  -2),
                           INT8_C(-105), INT8_C(  43), INT8_C( 116), INT8_C( -47),
                           INT8_C(  14), INT8_C(  41), INT8_C(  29), INT8_C(  -4),
                           INT8_C( -87), INT8_C( 114), INT8_C( -11), INT8_C(-103)),
      1, -11 }
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    int r = simde_mm256_extract_epi8(test_vec[i].a, test_vec[i].index);
    simde_assert_int(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_extract_epi16(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m256i a;
    int index;
    int r;
  } test_vec[8] = {
    { simde_mm256_set_epi16(INT16_C(-13852), INT16_C( -4342), INT16_C( 11109), INT16_C(-14025),
                            INT16_C(-31515), INT16_C(-26078), INT16_C( 28328), INT16_C( 27282),
                            INT16_C(   502), INT16_C(  4002), INT16_C(-24127), INT16_C(-19778),
                            INT16_C( -5333), INT16_C( -7161), INT16_C(  3486), INT16_C( 19428)),
       9,  28328 },
    { simde_mm256_set_epi16(INT16_C( 28377), INT16_C(  2705), INT16_C(-30669), INT16_C( 14223),
                            INT16_C(-12947), INT16_C(  3902), INT16_C(-31300), INT16_C(-16108),
                            INT16_C( 27185), INT16_C( 31404), INT16_C(  5864), INT16_C(-14684),
                            INT16_C(-16906), INT16_C(-22077), INT16_C( 29573), INT16_C(-29418)),
      14,   2705 },
    { simde_mm256_set_epi16(INT16_C(-27124), INT16_C( 25225), INT16_C(-21524), INT16_C(-25020),
                            INT16_C(-23283), INT16_C( 23354), INT16_C(  6766), INT16_C( 14439),
                            INT16_C( 30011), INT16_C( 12305), INT16_C( -6826), INT16_C( -1503),
                            INT16_C(-14868), INT16_C( -9131), INT16_C( 13807), INT16_C( 20111)),
       3, -14868 },
    { simde_mm256_set_epi16(INT16_C( -7451), INT16_C( 13959), INT16_C( 22108), INT16_C(-25977),
                            INT16_C( 24961), INT16_C(  5172), INT16_C(-22669), INT16_C( 24596),
                            INT16_C( -9625), INT16_C(  8329), INT16_C( 31660), INT16_C(  6372),
                            INT16_C( 22842), INT16_C( -8967), INT16_C(-28506), INT16_C(-25290)),
      15,  -7451 },
    { simde_mm256_set_epi16(INT16_C( -7088), INT16_C(-28965), INT16_C( 12247), INT16_C( 20030),
                            INT16_C(-11225), INT16_C(  9910), INT16_C(  8285), INT16_C(-29915),
                            INT16_C( 31449), INT16_C(-30562), INT16_C(  9135), INT16_C( -5794),
                            INT16_C(-28133), INT16_C( 19959), INT16_C( 11053), INT16_C( 15927)),
      14, -28965 },
    { simde_mm256_set_epi16(INT16_C(-29242), INT16_C( -8879), INT16_C( 20658), INT16_C(  6689),
                            INT16_C(-32364), INT16_C( -6586), INT16_C(-25712), INT16_C(-15508),
                            INT16_C(-18619), INT16_C(  3648), INT16_C(-11317), INT16_C(-24552),
                            INT16_C(  5053), INT16_C( 19407), INT16_C(  7336), INT16_C( 21360)),
      10,  -6586 },
    { simde_mm256_set_epi16(INT16_C(-14447), INT16_C( 22067), INT16_C( 23031), INT16_C( 30523),
                            INT16_C( 22048), INT16_C( 13854), INT16_C(  3679), INT16_C( -6779),
                            INT16_C(-19554), INT16_C( -6724), INT16_C( -2267), INT16_C(-22355),
                            INT16_C(-10286), INT16_C(-26978), INT16_C(-13753), INT16_C(-10708)),
       6,  -6724 },
    { simde_mm256_set_epi16(INT16_C(-19975), INT16_C(-21187), INT16_C(-14562), INT16_C(-29768),
                            INT16_C(  5795), INT16_C(  3174), INT16_C(-13080), INT16_C(  1359),
                            INT16_C(-14826), INT16_C( 14059), INT16_C(  6182), INT16_C(  5609),
                            INT16_C(-12873), INT16_C(-31886), INT16_C(-22495), INT16_C( -9770)),
      12, -29768 }
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    int r = simde_mm256_extract_epi16(test_vec[i].a, test_vec[i].index);
    simde_assert_int(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_extracti128_si256(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m256i a;
    simde__m256i b;
    simde__m128i ra;
    simde__m128i rb;
  } test_vec[8] = {
    { simde_mm256_set_epi32(INT32_C( 1229394801), INT32_C(  992221618), INT32_C(-1388107406), INT32_C(  780445625),
                            INT32_C( 1795700153), INT32_C( -297324271), INT32_C( 1549329146), INT32_C( -534963225)),
      simde_mm256_set_epi32(INT32_C( -867719772), INT32_C(-1804212438), INT32_C( 1849818353), INT32_C(  405560893),
                            INT32_C( 1351338386), INT32_C( -886724662), INT32_C( 1197680760), INT32_C( 1003042592)),
      simde_mm_set_epi32(INT32_C( 1795700153), INT32_C( -297324271), INT32_C( 1549329146), INT32_C( -534963225)),
      simde_mm_set_epi32(INT32_C( 1229394801), INT32_C(  992221618), INT32_C(-1388107406), INT32_C(  780445625)) },
    { simde_mm256_set_epi32(INT32_C( 1839397279), INT32_C( -585358334), INT32_C(  779178160), INT32_C( -362976984),
                            INT32_C(-1015866216), INT32_C( -556342867), INT32_C( -766379029), INT32_C( -130781639)),
      simde_mm256_set_epi32(INT32_C( 2021215895), INT32_C( -422044488), INT32_C(-1385706777), INT32_C(   22702781),
                            INT32_C( 1076807274), INT32_C(-1923875401), INT32_C( -554846936), INT32_C(-1008226174)),
      simde_mm_set_epi32(INT32_C(-1015866216), INT32_C( -556342867), INT32_C( -766379029), INT32_C( -130781639)),
      simde_mm_set_epi32(INT32_C( 1839397279), INT32_C( -585358334), INT32_C(  779178160), INT32_C( -362976984)) },
    { simde_mm256_set_epi32(INT32_C(   23865749), INT32_C( -908972624), INT32_C(-1642418179), INT32_C(  111689864),
                            INT32_C( -835154412), INT32_C( -431540196), INT32_C( -161564683), INT32_C(  204589457)),
      simde_mm256_set_epi32(INT32_C( 2088662618), INT32_C(-1671363325), INT32_C( -997695043), INT32_C( -809764814),
                            INT32_C( 2092581708), INT32_C(-1073689737), INT32_C(-1556963227), INT32_C( -641330488)),
      simde_mm_set_epi32(INT32_C( -835154412), INT32_C( -431540196), INT32_C( -161564683), INT32_C(  204589457)),
      simde_mm_set_epi32(INT32_C(   23865749), INT32_C( -908972624), INT32_C(-1642418179), INT32_C(  111689864)) },
    { simde_mm256_set_epi32(INT32_C( 1727711569), INT32_C(-1915329589), INT32_C( -979233658), INT32_C( -409203179),
                            INT32_C( 1343207861), INT32_C(-1541174422), INT32_C(-2097250480), INT32_C(-1382492089)),
      simde_mm256_set_epi32(INT32_C(  -42175512), INT32_C(-2146588690), INT32_C(-1902868938), INT32_C( 1919945739),
                            INT32_C(  410749235), INT32_C(-1828962645), INT32_C(  525862553), INT32_C( -282512400)),
      simde_mm_set_epi32(INT32_C( 1343207861), INT32_C(-1541174422), INT32_C(-2097250480), INT32_C(-1382492089)),
      simde_mm_set_epi32(INT32_C( 1727711569), INT32_C(-1915329589), INT32_C( -979233658), INT32_C( -409203179)) },
    { simde_mm256_set_epi32(INT32_C(  377369527), INT32_C( 1159197718), INT32_C(  288677560), INT32_C(  828517622),
                            INT32_C( 1815109517), INT32_C( 1103735854), INT32_C( 1342116414), INT32_C( 1750949195)),
      simde_mm256_set_epi32(INT32_C( 1481955155), INT32_C( -119794855), INT32_C(-2109995042), INT32_C(  582656481),
                            INT32_C( 1178951500), INT32_C(  762286037), INT32_C(  628377158), INT32_C( -188026020)),
      simde_mm_set_epi32(INT32_C( 1815109517), INT32_C( 1103735854), INT32_C( 1342116414), INT32_C( 1750949195)),
      simde_mm_set_epi32(INT32_C(  377369527), INT32_C( 1159197718), INT32_C(  288677560), INT32_C(  828517622)) },
    { simde_mm256_set_epi32(INT32_C(-1996051424), INT32_C( -314294760), INT32_C( -770521150), INT32_C(  508113145),
                            INT32_C( -677093043), INT32_C( -527636644), INT32_C( 1238565466), INT32_C(-1592387355)),
      simde_mm256_set_epi32(INT32_C(-1510707643), INT32_C( 1988531398), INT32_C(-1182276921), INT32_C(  363503044),
                            INT32_C( 2086268932), INT32_C( -428647595), INT32_C( 1685321543), INT32_C( 1979089365)),
      simde_mm_set_epi32(INT32_C( -677093043), INT32_C( -527636644), INT32_C( 1238565466), INT32_C(-1592387355)),
      simde_mm_set_epi32(INT32_C(-1996051424), INT32_C( -314294760), INT32_C( -770521150), INT32_C(  508113145)) },
    { simde_mm256_set_epi32(INT32_C(    4593159), INT32_C( 1779671737), INT32_C( -569674634), INT32_C( -184254965),
                            INT32_C( -665786654), INT32_C(  663766301), INT32_C(-1237697897), INT32_C( -260948936)),
      simde_mm256_set_epi32(INT32_C( -575114102), INT32_C( -399786699), INT32_C(-1468780124), INT32_C( 2032090700),
                            INT32_C(  723386747), INT32_C(-1766232746), INT32_C(   73837413), INT32_C(  496540408)),
      simde_mm_set_epi32(INT32_C( -665786654), INT32_C(  663766301), INT32_C(-1237697897), INT32_C( -260948936)),
      simde_mm_set_epi32(INT32_C(    4593159), INT32_C( 1779671737), INT32_C( -569674634), INT32_C( -184254965)) },
    { simde_mm256_set_epi32(INT32_C( -328197013), INT32_C( 1036318270), INT32_C(-1930293157), INT32_C( 1948339432),
                            INT32_C( 1903716614), INT32_C(-1951673698), INT32_C(-1858071379), INT32_C( 2070124471)),
      simde_mm256_set_epi32(INT32_C(-1815372819), INT32_C( -102535612), INT32_C(  115383384), INT32_C( 1004544095),
                            INT32_C( 1506420054), INT32_C(-1014523798), INT32_C(-1776388104), INT32_C( 1550371104)),
      simde_mm_set_epi32(INT32_C( 1903716614), INT32_C(-1951673698), INT32_C(-1858071379), INT32_C( 2070124471)),
      simde_mm_set_epi32(INT32_C( -328197013), INT32_C( 1036318270), INT32_C(-1930293157), INT32_C( 1948339432)) }
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m128i ra = simde_mm256_extracti128_si256(test_vec[i].a, 0);
    simde__m128i rb = simde_mm256_extracti128_si256(test_vec[i].a, 1);
    simde_assert_m128i_i32(ra, ==, test_vec[i].ra);
    simde_assert_m128i_i32(rb, ==, test_vec[i].rb);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_max_epi16(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m256i a;
    simde__m256i b;
    simde__m256i r;
  } test_vec[8] = {
   { simde_mm256_set_epi16(INT16_C( 13945), INT16_C(-32397), INT16_C( -8500), INT16_C(-16936),
                            INT16_C(  -615), INT16_C( 28879), INT16_C( 19952), INT16_C(-20844),
                            INT16_C(-18762), INT16_C( 23311), INT16_C(-22090), INT16_C( 16355),
                            INT16_C( 18939), INT16_C( -9393), INT16_C( 19655), INT16_C( 25483)),
      simde_mm256_set_epi16(INT16_C(-30076), INT16_C(-27428), INT16_C(-24061), INT16_C( -9620),
                            INT16_C(-17974), INT16_C(  3150), INT16_C(  6986), INT16_C(-23891),
                            INT16_C( 12942), INT16_C( 12645), INT16_C(-13904), INT16_C(  -868),
                            INT16_C(-14591), INT16_C( 24935), INT16_C(  4654), INT16_C(  4591)),
      simde_mm256_set_epi16(INT16_C( 13945), INT16_C(-27428), INT16_C( -8500), INT16_C( -9620),
                            INT16_C(  -615), INT16_C( 28879), INT16_C( 19952), INT16_C(-20844),
                            INT16_C( 12942), INT16_C( 23311), INT16_C(-13904), INT16_C( 16355),
                            INT16_C( 18939), INT16_C( 24935), INT16_C( 19655), INT16_C( 25483)) },
    { simde_mm256_set_epi16(INT16_C( 15746), INT16_C( 16476), INT16_C(-26892), INT16_C( 15551),
                            INT16_C(  4802), INT16_C( 22020), INT16_C(  7684), INT16_C( 20433),
                            INT16_C(-15213), INT16_C( -9067), INT16_C( 11028), INT16_C(  2768),
                            INT16_C( 19036), INT16_C(-29021), INT16_C( 27796), INT16_C(-20181)),
      simde_mm256_set_epi16(INT16_C(-15017), INT16_C(-10120), INT16_C(-23789), INT16_C(-21730),
                            INT16_C( 16078), INT16_C(  3607), INT16_C(-18668), INT16_C(-12209),
                            INT16_C(  -562), INT16_C( 30247), INT16_C( 20324), INT16_C( -8924),
                            INT16_C( 24524), INT16_C( -5426), INT16_C( 25503), INT16_C(  2215)),
      simde_mm256_set_epi16(INT16_C( 15746), INT16_C( 16476), INT16_C(-23789), INT16_C( 15551),
                            INT16_C( 16078), INT16_C( 22020), INT16_C(  7684), INT16_C( 20433),
                            INT16_C(  -562), INT16_C( 30247), INT16_C( 20324), INT16_C(  2768),
                            INT16_C( 24524), INT16_C( -5426), INT16_C( 27796), INT16_C(  2215)) },
    { simde_mm256_set_epi16(INT16_C(  9558), INT16_C( 24602), INT16_C(-11854), INT16_C( 13316),
                            INT16_C( -7111), INT16_C(  5322), INT16_C( 10474), INT16_C( 14309),
                            INT16_C( 10175), INT16_C(-23285), INT16_C( -7105), INT16_C(-18408),
                            INT16_C( -9456), INT16_C(-31797), INT16_C(  6677), INT16_C( 24246)),
      simde_mm256_set_epi16(INT16_C(  8353), INT16_C(-12225), INT16_C( 10989), INT16_C( 20160),
                            INT16_C(-24928), INT16_C( 11285), INT16_C(-21080), INT16_C(-21637),
                            INT16_C(  -557), INT16_C(-15431), INT16_C(-14247), INT16_C(  1813),
                            INT16_C( -7571), INT16_C( 22502), INT16_C( 12550), INT16_C(  3083)),
      simde_mm256_set_epi16(INT16_C(  9558), INT16_C( 24602), INT16_C( 10989), INT16_C( 20160),
                            INT16_C( -7111), INT16_C( 11285), INT16_C( 10474), INT16_C( 14309),
                            INT16_C( 10175), INT16_C(-15431), INT16_C( -7105), INT16_C(  1813),
                            INT16_C( -7571), INT16_C( 22502), INT16_C( 12550), INT16_C( 24246)) },
    { simde_mm256_set_epi16(INT16_C( 25542), INT16_C(-21715), INT16_C(-12723), INT16_C(  3641),
                            INT16_C( 10626), INT16_C(  1975), INT16_C( 32038), INT16_C( 13257),
                            INT16_C( 26030), INT16_C(-29459), INT16_C( 27784), INT16_C(-29348),
                            INT16_C( 24986), INT16_C( 19201), INT16_C(-21133), INT16_C(  -544)),
      simde_mm256_set_epi16(INT16_C(-15360), INT16_C( -9091), INT16_C(  9964), INT16_C(-26119),
                            INT16_C(-13193), INT16_C( -4473), INT16_C(-16910), INT16_C( -8355),
                            INT16_C( 29088), INT16_C( 26903), INT16_C( 19970), INT16_C( 20929),
                            INT16_C( 21866), INT16_C(  -554), INT16_C(-31252), INT16_C(-27281)),
      simde_mm256_set_epi16(INT16_C( 25542), INT16_C( -9091), INT16_C(  9964), INT16_C(  3641),
                            INT16_C( 10626), INT16_C(  1975), INT16_C( 32038), INT16_C( 13257),
                            INT16_C( 29088), INT16_C( 26903), INT16_C( 27784), INT16_C( 20929),
                            INT16_C( 24986), INT16_C( 19201), INT16_C(-21133), INT16_C(  -544)) },
    { simde_mm256_set_epi16(INT16_C(-28957), INT16_C(  7788), INT16_C(-11350), INT16_C( 29385),
                            INT16_C( -7207), INT16_C(-21363), INT16_C(-10963), INT16_C(-23177),
                            INT16_C( 22883), INT16_C(-14765), INT16_C( 17155), INT16_C(-19202),
                            INT16_C(-32343), INT16_C(  8167), INT16_C( 17107), INT16_C(-17194)),
      simde_mm256_set_epi16(INT16_C(-21587), INT16_C( 21036), INT16_C( 16036), INT16_C(-20844),
                            INT16_C(  2600), INT16_C(-15232), INT16_C(  4125), INT16_C( 22708),
                            INT16_C(-29000), INT16_C(-22285), INT16_C(  8338), INT16_C( 25191),
                            INT16_C(  5401), INT16_C(-28508), INT16_C(-16518), INT16_C(-23781)),
      simde_mm256_set_epi16(INT16_C(-21587), INT16_C( 21036), INT16_C( 16036), INT16_C( 29385),
                            INT16_C(  2600), INT16_C(-15232), INT16_C(  4125), INT16_C( 22708),
                            INT16_C( 22883), INT16_C(-14765), INT16_C( 17155), INT16_C( 25191),
                            INT16_C(  5401), INT16_C(  8167), INT16_C( 17107), INT16_C(-17194)) },
    { simde_mm256_set_epi16(INT16_C( 26823), INT16_C( 30422), INT16_C(-10399), INT16_C(  6469),
                            INT16_C(-22608), INT16_C(  3602), INT16_C( 24356), INT16_C( -5312),
                            INT16_C( 22553), INT16_C(  4057), INT16_C( 16984), INT16_C( 14642),
                            INT16_C( -4725), INT16_C(-13132), INT16_C(-32486), INT16_C( -9795)),
      simde_mm256_set_epi16(INT16_C(-16670), INT16_C( 11037), INT16_C(-12867), INT16_C( -9733),
                            INT16_C(-19057), INT16_C( 28626), INT16_C( 27349), INT16_C( 21991),
                            INT16_C(-17860), INT16_C( -7267), INT16_C( 21708), INT16_C( 27219),
                            INT16_C(  3344), INT16_C(-13000), INT16_C( -5702), INT16_C(  8873)),
      simde_mm256_set_epi16(INT16_C( 26823), INT16_C( 30422), INT16_C(-10399), INT16_C(  6469),
                            INT16_C(-19057), INT16_C( 28626), INT16_C( 27349), INT16_C( 21991),
                            INT16_C( 22553), INT16_C(  4057), INT16_C( 21708), INT16_C( 27219),
                            INT16_C(  3344), INT16_C(-13000), INT16_C( -5702), INT16_C(  8873)) },
    { simde_mm256_set_epi16(INT16_C( 28327), INT16_C( 28059), INT16_C(-12455), INT16_C(-22892),
                            INT16_C(  9516), INT16_C(-23091), INT16_C( 28067), INT16_C( 29028),
                            INT16_C(-24610), INT16_C(-13303), INT16_C( -3871), INT16_C( 25753),
                            INT16_C(-19764), INT16_C(-10115), INT16_C( -9313), INT16_C(-10807)),
      simde_mm256_set_epi16(INT16_C(  1267), INT16_C( -7929), INT16_C( 29505), INT16_C( 22745),
                            INT16_C(  1801), INT16_C(  -829), INT16_C(  2659), INT16_C( 24204),
                            INT16_C( 27266), INT16_C(-10805), INT16_C(  7071), INT16_C( 12404),
                            INT16_C( 27748), INT16_C( 11490), INT16_C(-10130), INT16_C(  7320)),
      simde_mm256_set_epi16(INT16_C( 28327), INT16_C( 28059), INT16_C( 29505), INT16_C( 22745),
                            INT16_C(  9516), INT16_C(  -829), INT16_C( 28067), INT16_C( 29028),
                            INT16_C( 27266), INT16_C(-10805), INT16_C(  7071), INT16_C( 25753),
                            INT16_C( 27748), INT16_C( 11490), INT16_C( -9313), INT16_C(  7320)) },
    { simde_mm256_set_epi16(INT16_C(-28396), INT16_C(  3489), INT16_C( 18687), INT16_C( 31879),
                            INT16_C( 15536), INT16_C(-17843), INT16_C( 25087), INT16_C(-27693),
                            INT16_C(-17170), INT16_C( 22369), INT16_C(-27360), INT16_C( -5829),
                            INT16_C(-28550), INT16_C(   650), INT16_C(-11446), INT16_C(  3172)),
      simde_mm256_set_epi16(INT16_C(-17057), INT16_C(-18950), INT16_C( 15210), INT16_C(-25469),
                            INT16_C(-29475), INT16_C( 24211), INT16_C(-14409), INT16_C( -9847),
                            INT16_C( 14530), INT16_C(-24184), INT16_C(-29404), INT16_C(  9879),
                            INT16_C(  2544), INT16_C(-17943), INT16_C(  7392), INT16_C( 21259)),
      simde_mm256_set_epi16(INT16_C(-17057), INT16_C(  3489), INT16_C( 18687), INT16_C( 31879),
                            INT16_C( 15536), INT16_C( 24211), INT16_C( 25087), INT16_C( -9847),
                            INT16_C( 14530), INT16_C( 22369), INT16_C(-27360), INT16_C(  9879),
                            INT16_C(  2544), INT16_C(   650), INT16_C(  7392), INT16_C( 21259)) },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_max_epi16(test_vec[i].a, test_vec[i].b);
    simde_assert_m256i_i16(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_max_epi32(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m256i a;
    simde__m256i b;
    simde__m256i r;
  } test_vec[8] = {
    { simde_mm256_set_epi32(INT32_C(-1578701412), INT32_C(-1861943275), INT32_C( 1717826073), INT32_C( -689858277),
                            INT32_C(-2120069619), INT32_C( -269745295), INT32_C(  993893699), INT32_C( 1747535129)),
      simde_mm256_set_epi32(INT32_C(-1662415513), INT32_C(  528745592), INT32_C( -219858588), INT32_C(  622357704),
                            INT32_C(-2013314779), INT32_C(-1188086430), INT32_C( 1171120200), INT32_C(  259652605)),
      simde_mm256_set_epi32(INT32_C(-1578701412), INT32_C(  528745592), INT32_C( 1717826073), INT32_C(  622357704),
                            INT32_C(-2013314779), INT32_C( -269745295), INT32_C( 1171120200), INT32_C( 1747535129)) },
    { simde_mm256_set_epi32(INT32_C( 1892880717), INT32_C(  489135272), INT32_C( 1334433155), INT32_C(  820950025),
                            INT32_C(  875780372), INT32_C( 1165542940), INT32_C(-1922521413), INT32_C( 1603602866)),
      simde_mm256_set_epi32(INT32_C( 1774078122), INT32_C(  717307143), INT32_C( 1385706638), INT32_C( 1722931608),
                            INT32_C(  722989282), INT32_C(  346685962), INT32_C(  888351034), INT32_C(-1040558861)),
      simde_mm256_set_epi32(INT32_C( 1892880717), INT32_C(  717307143), INT32_C( 1385706638), INT32_C( 1722931608),
                            INT32_C(  875780372), INT32_C( 1165542940), INT32_C(  888351034), INT32_C( 1603602866)) },
    { simde_mm256_set_epi32(INT32_C(  542527818), INT32_C(  704072326), INT32_C(-1102544845), INT32_C( 1444592706),
                            INT32_C(-1925092178), INT32_C( -204731801), INT32_C(  775742710), INT32_C( 1177505754)),
      simde_mm256_set_epi32(INT32_C( -551142491), INT32_C(  444795418), INT32_C( -825745617), INT32_C(-1787304548),
                            INT32_C(-1241777147), INT32_C(  265612525), INT32_C( 2134936507), INT32_C(-1780599144)),
      simde_mm256_set_epi32(INT32_C(  542527818), INT32_C(  704072326), INT32_C( -825745617), INT32_C( 1444592706),
                            INT32_C(-1241777147), INT32_C(  265612525), INT32_C( 2134936507), INT32_C( 1177505754)) },
    { simde_mm256_set_epi32(INT32_C(  788610578), INT32_C( 1831830497), INT32_C( -755374494), INT32_C( 2130364415),
                            INT32_C( -342185910), INT32_C(  854700402), INT32_C( 1343385181), INT32_C(  891289886)),
      simde_mm256_set_epi32(INT32_C( 1917738489), INT32_C(  690751883), INT32_C(-1037858966), INT32_C(-1567909551),
                            INT32_C(  -26783282), INT32_C( -715472333), INT32_C( -713074037), INT32_C(  -17697982)),
      simde_mm256_set_epi32(INT32_C( 1917738489), INT32_C( 1831830497), INT32_C( -755374494), INT32_C( 2130364415),
                            INT32_C(  -26783282), INT32_C(  854700402), INT32_C( 1343385181), INT32_C(  891289886)) },
    { simde_mm256_set_epi32(INT32_C( 1796568981), INT32_C(-1846046069), INT32_C(-1495880353), INT32_C(-1105562137),
                            INT32_C(-2000119429), INT32_C(  450352139), INT32_C( -734796291), INT32_C(-1851159287)),
      simde_mm256_set_epi32(INT32_C( 1076027923), INT32_C( 1999677975), INT32_C( -498539521), INT32_C(-1166856281),
                            INT32_C(-1611419248), INT32_C(-1268341170), INT32_C(-1115547457), INT32_C( 1554907000)),
      simde_mm256_set_epi32(INT32_C( 1796568981), INT32_C( 1999677975), INT32_C( -498539521), INT32_C(-1105562137),
                            INT32_C(-1611419248), INT32_C(  450352139), INT32_C( -734796291), INT32_C( 1554907000)) },
    { simde_mm256_set_epi32(INT32_C( -263364521), INT32_C( 1666932430), INT32_C(  378039954), INT32_C( 1866502452),
                            INT32_C( -756222443), INT32_C( -752660448), INT32_C( 1087715357), INT32_C( 1808069656)),
      simde_mm256_set_epi32(INT32_C(   10375777), INT32_C(  958545984), INT32_C(-1916055393), INT32_C(-1450264731),
                            INT32_C( -550755823), INT32_C( 2131394316), INT32_C(  243861812), INT32_C( 1031114919)),
      simde_mm256_set_epi32(INT32_C(   10375777), INT32_C( 1666932430), INT32_C(  378039954), INT32_C( 1866502452),
                            INT32_C( -550755823), INT32_C( 2131394316), INT32_C( 1087715357), INT32_C( 1808069656)) },
    { simde_mm256_set_epi32(INT32_C(-1075159077), INT32_C( -789508054), INT32_C(-2102436600), INT32_C(  177892995),
                            INT32_C(-1910430929), INT32_C( -135620958), INT32_C( 1899951190), INT32_C(-1286116105)),
      simde_mm256_set_epi32(INT32_C(-1117240644), INT32_C(-1011771686), INT32_C(-1764247251), INT32_C( -953836385),
                            INT32_C(-1633093106), INT32_C( 1815106343), INT32_C( 1418749534), INT32_C( 1718021188)),
      simde_mm256_set_epi32(INT32_C(-1075159077), INT32_C( -789508054), INT32_C(-1764247251), INT32_C(  177892995),
                            INT32_C(-1633093106), INT32_C( 1815106343), INT32_C( 1899951190), INT32_C( 1718021188)) },
    { simde_mm256_set_epi32(INT32_C( -585726505), INT32_C( -735532451), INT32_C( 1572773329), INT32_C(-1610167093),
                            INT32_C(  934479765), INT32_C( 1726304740), INT32_C(-1433078949), INT32_C(-1056217637)),
      simde_mm256_set_epi32(INT32_C(  201330788), INT32_C( 1825214883), INT32_C(  489777084), INT32_C( -824102072),
                            INT32_C(-1255028012), INT32_C(-1300324544), INT32_C(-1269112569), INT32_C( -124131174)),
      simde_mm256_set_epi32(INT32_C(  201330788), INT32_C( 1825214883), INT32_C( 1572773329), INT32_C( -824102072),
                            INT32_C(  934479765), INT32_C( 1726304740), INT32_C(-1269112569), INT32_C( -124131174)) },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_max_epi32(test_vec[i].a, test_vec[i].b);
    simde_assert_m256i_i32(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_min_epu8(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m256i a;
    simde__m256i b;
    simde__m256i r;
  } test_vec[8] = {
    { simde_x_mm256_set_epu8(UINT8_C( 83), UINT8_C( 77), UINT8_C(142), UINT8_C(252),
                             UINT8_C( 19), UINT8_C( 26), UINT8_C(193), UINT8_C( 92),
                             UINT8_C(253), UINT8_C(183), UINT8_C(225), UINT8_C(205),
                             UINT8_C(165), UINT8_C( 19), UINT8_C(154), UINT8_C(158),
                             UINT8_C(126), UINT8_C(221), UINT8_C(206), UINT8_C( 22),
                             UINT8_C(217), UINT8_C(166), UINT8_C(237), UINT8_C(161),
                             UINT8_C(207), UINT8_C( 26), UINT8_C( 36), UINT8_C( 78),
                             UINT8_C( 55), UINT8_C(167), UINT8_C( 36), UINT8_C(198)),
      simde_x_mm256_set_epu8(UINT8_C(203), UINT8_C( 44), UINT8_C( 47), UINT8_C( 51),
                             UINT8_C(185), UINT8_C( 39), UINT8_C(221), UINT8_C( 75),
                             UINT8_C(182), UINT8_C(100), UINT8_C(238), UINT8_C(172),
                             UINT8_C(248), UINT8_C(164), UINT8_C( 91), UINT8_C(138),
                             UINT8_C(128), UINT8_C( 29), UINT8_C(136), UINT8_C(164),
                             UINT8_C( 43), UINT8_C( 85), UINT8_C(168), UINT8_C(105),
                             UINT8_C(240), UINT8_C(205), UINT8_C(221), UINT8_C(217),
                             UINT8_C(244), UINT8_C(220), UINT8_C(102), UINT8_C( 37)),
      simde_x_mm256_set_epu8(UINT8_C( 83), UINT8_C( 44), UINT8_C( 47), UINT8_C( 51),
                             UINT8_C( 19), UINT8_C( 26), UINT8_C(193), UINT8_C( 75),
                             UINT8_C(182), UINT8_C(100), UINT8_C(225), UINT8_C(172),
                             UINT8_C(165), UINT8_C( 19), UINT8_C( 91), UINT8_C(138),
                             UINT8_C(126), UINT8_C( 29), UINT8_C(136), UINT8_C( 22),
                             UINT8_C( 43), UINT8_C( 85), UINT8_C(168), UINT8_C(105),
                             UINT8_C(207), UINT8_C( 26), UINT8_C( 36), UINT8_C( 78),
                             UINT8_C( 55), UINT8_C(167), UINT8_C( 36), UINT8_C( 37)) },
    { simde_x_mm256_set_epu8(UINT8_C(177), UINT8_C(210), UINT8_C( 28), UINT8_C(116),
                             UINT8_C(174), UINT8_C(162), UINT8_C(241), UINT8_C( 21),
                             UINT8_C(126), UINT8_C(202), UINT8_C(250), UINT8_C(169),
                             UINT8_C( 43), UINT8_C(239), UINT8_C(224), UINT8_C(202),
                             UINT8_C(208), UINT8_C( 48), UINT8_C(132), UINT8_C( 78),
                             UINT8_C( 59), UINT8_C(  2), UINT8_C(213), UINT8_C(228),
                             UINT8_C( 42), UINT8_C( 45), UINT8_C(244), UINT8_C( 41),
                             UINT8_C( 49), UINT8_C( 48), UINT8_C(111), UINT8_C(211)),
      simde_x_mm256_set_epu8(UINT8_C(114), UINT8_C( 33), UINT8_C(210), UINT8_C(232),
                             UINT8_C(128), UINT8_C(122), UINT8_C(216), UINT8_C(228),
                             UINT8_C( 91), UINT8_C( 37), UINT8_C(119), UINT8_C(203),
                             UINT8_C(236), UINT8_C( 24), UINT8_C(170), UINT8_C(120),
                             UINT8_C( 95), UINT8_C(231), UINT8_C(152), UINT8_C(143),
                             UINT8_C( 42), UINT8_C( 38), UINT8_C(240), UINT8_C(125),
                             UINT8_C(124), UINT8_C(251), UINT8_C(118), UINT8_C( 44),
                             UINT8_C( 68), UINT8_C( 42), UINT8_C( 54), UINT8_C(185)),
      simde_x_mm256_set_epu8(UINT8_C(114), UINT8_C( 33), UINT8_C( 28), UINT8_C(116),
                             UINT8_C(128), UINT8_C(122), UINT8_C(216), UINT8_C( 21),
                             UINT8_C( 91), UINT8_C( 37), UINT8_C(119), UINT8_C(169),
                             UINT8_C( 43), UINT8_C( 24), UINT8_C(170), UINT8_C(120),
                             UINT8_C( 95), UINT8_C( 48), UINT8_C(132), UINT8_C( 78),
                             UINT8_C( 42), UINT8_C(  2), UINT8_C(213), UINT8_C(125),
                             UINT8_C( 42), UINT8_C( 45), UINT8_C(118), UINT8_C( 41),
                             UINT8_C( 49), UINT8_C( 42), UINT8_C( 54), UINT8_C(185)) },
    { simde_x_mm256_set_epu8(UINT8_C( 78), UINT8_C( 16), UINT8_C( 42), UINT8_C(217),
                             UINT8_C(  5), UINT8_C( 96), UINT8_C(  7), UINT8_C( 83),
                             UINT8_C( 16), UINT8_C(208), UINT8_C(  1), UINT8_C(207),
                             UINT8_C( 75), UINT8_C(207), UINT8_C(252), UINT8_C( 92),
                             UINT8_C(122), UINT8_C( 24), UINT8_C( 32), UINT8_C(104),
                             UINT8_C( 88), UINT8_C( 59), UINT8_C(218), UINT8_C( 28),
                             UINT8_C( 51), UINT8_C( 64), UINT8_C( 65), UINT8_C( 92),
                             UINT8_C( 24), UINT8_C( 83), UINT8_C(248), UINT8_C(243)),
      simde_x_mm256_set_epu8(UINT8_C(167), UINT8_C( 87), UINT8_C( 75), UINT8_C( 10),
                             UINT8_C( 44), UINT8_C(173), UINT8_C(210), UINT8_C(150),
                             UINT8_C(187), UINT8_C(229), UINT8_C(246), UINT8_C( 10),
                             UINT8_C( 80), UINT8_C( 74), UINT8_C(174), UINT8_C(128),
                             UINT8_C( 64), UINT8_C(160), UINT8_C(126), UINT8_C(231),
                             UINT8_C(215), UINT8_C( 80), UINT8_C(115), UINT8_C( 66),
                             UINT8_C(204), UINT8_C( 18), UINT8_C(158), UINT8_C(133),
                             UINT8_C(170), UINT8_C(119), UINT8_C(216), UINT8_C(196)),
      simde_x_mm256_set_epu8(UINT8_C( 78), UINT8_C( 16), UINT8_C( 42), UINT8_C( 10),
                             UINT8_C(  5), UINT8_C( 96), UINT8_C(  7), UINT8_C( 83),
                             UINT8_C( 16), UINT8_C(208), UINT8_C(  1), UINT8_C( 10),
                             UINT8_C( 75), UINT8_C( 74), UINT8_C(174), UINT8_C( 92),
                             UINT8_C( 64), UINT8_C( 24), UINT8_C( 32), UINT8_C(104),
                             UINT8_C( 88), UINT8_C( 59), UINT8_C(115), UINT8_C( 28),
                             UINT8_C( 51), UINT8_C( 18), UINT8_C( 65), UINT8_C( 92),
                             UINT8_C( 24), UINT8_C( 83), UINT8_C(216), UINT8_C(196)) },
    { simde_x_mm256_set_epu8(UINT8_C(  4), UINT8_C(145), UINT8_C( 75), UINT8_C( 42),
                             UINT8_C( 60), UINT8_C(146), UINT8_C(158), UINT8_C(  3),
                             UINT8_C( 57), UINT8_C(210), UINT8_C( 14), UINT8_C(106),
                             UINT8_C( 96), UINT8_C(136), UINT8_C( 82), UINT8_C( 54),
                             UINT8_C(227), UINT8_C(202), UINT8_C( 35), UINT8_C(184),
                             UINT8_C( 41), UINT8_C(205), UINT8_C(162), UINT8_C(206),
                             UINT8_C(247), UINT8_C( 69), UINT8_C(139), UINT8_C(186),
                             UINT8_C( 13), UINT8_C(119), UINT8_C( 79), UINT8_C( 53)),
      simde_x_mm256_set_epu8(UINT8_C(239), UINT8_C(239), UINT8_C( 37), UINT8_C(187),
                             UINT8_C(237), UINT8_C(203), UINT8_C( 68), UINT8_C( 35),
                             UINT8_C(147), UINT8_C(109), UINT8_C(244), UINT8_C(194),
                             UINT8_C(131), UINT8_C(189), UINT8_C( 51), UINT8_C( 84),
                             UINT8_C( 48), UINT8_C( 26), UINT8_C(203), UINT8_C( 35),
                             UINT8_C(128), UINT8_C( 76), UINT8_C( 16), UINT8_C( 52),
                             UINT8_C(103), UINT8_C(192), UINT8_C(105), UINT8_C( 65),
                             UINT8_C(117), UINT8_C(100), UINT8_C( 71), UINT8_C(124)),
      simde_x_mm256_set_epu8(UINT8_C(  4), UINT8_C(145), UINT8_C( 37), UINT8_C( 42),
                             UINT8_C( 60), UINT8_C(146), UINT8_C( 68), UINT8_C(  3),
                             UINT8_C( 57), UINT8_C(109), UINT8_C( 14), UINT8_C(106),
                             UINT8_C( 96), UINT8_C(136), UINT8_C( 51), UINT8_C( 54),
                             UINT8_C( 48), UINT8_C( 26), UINT8_C( 35), UINT8_C( 35),
                             UINT8_C( 41), UINT8_C( 76), UINT8_C( 16), UINT8_C( 52),
                             UINT8_C(103), UINT8_C( 69), UINT8_C(105), UINT8_C( 65),
                             UINT8_C( 13), UINT8_C(100), UINT8_C( 71), UINT8_C( 53)) },
    { simde_x_mm256_set_epu8(UINT8_C(144), UINT8_C(140), UINT8_C(121), UINT8_C(161),
                             UINT8_C(  2), UINT8_C( 56), UINT8_C(102), UINT8_C(220),
                             UINT8_C(246), UINT8_C( 67), UINT8_C( 19), UINT8_C( 67),
                             UINT8_C( 18), UINT8_C(117), UINT8_C(155), UINT8_C( 84),
                             UINT8_C(  3), UINT8_C(204), UINT8_C( 72), UINT8_C( 34),
                             UINT8_C(218), UINT8_C(208), UINT8_C( 99), UINT8_C( 27),
                             UINT8_C(224), UINT8_C( 99), UINT8_C(119), UINT8_C(221),
                             UINT8_C( 98), UINT8_C(202), UINT8_C(146), UINT8_C( 18)),
      simde_x_mm256_set_epu8(UINT8_C(127), UINT8_C(108), UINT8_C( 76), UINT8_C(146),
                             UINT8_C(206), UINT8_C(221), UINT8_C(206), UINT8_C(168),
                             UINT8_C( 11), UINT8_C(166), UINT8_C(228), UINT8_C(131),
                             UINT8_C( 46), UINT8_C( 42), UINT8_C(192), UINT8_C(117),
                             UINT8_C(166), UINT8_C(151), UINT8_C(189), UINT8_C(138),
                             UINT8_C(121), UINT8_C( 19), UINT8_C( 89), UINT8_C(188),
                             UINT8_C(255), UINT8_C(104), UINT8_C(124), UINT8_C(206),
                             UINT8_C( 89), UINT8_C(160), UINT8_C(162), UINT8_C( 10)),
      simde_x_mm256_set_epu8(UINT8_C(127), UINT8_C(108), UINT8_C( 76), UINT8_C(146),
                             UINT8_C(  2), UINT8_C( 56), UINT8_C(102), UINT8_C(168),
                             UINT8_C( 11), UINT8_C( 67), UINT8_C( 19), UINT8_C( 67),
                             UINT8_C( 18), UINT8_C( 42), UINT8_C(155), UINT8_C( 84),
                             UINT8_C(  3), UINT8_C(151), UINT8_C( 72), UINT8_C( 34),
                             UINT8_C(121), UINT8_C( 19), UINT8_C( 89), UINT8_C( 27),
                             UINT8_C(224), UINT8_C( 99), UINT8_C(119), UINT8_C(206),
                             UINT8_C( 89), UINT8_C(160), UINT8_C(146), UINT8_C( 10)) },
    { simde_x_mm256_set_epu8(UINT8_C( 74), UINT8_C(143), UINT8_C( 19), UINT8_C(  8),
                             UINT8_C( 11), UINT8_C(124), UINT8_C( 76), UINT8_C(  6),
                             UINT8_C(148), UINT8_C( 67), UINT8_C(224), UINT8_C(163),
                             UINT8_C(113), UINT8_C(245), UINT8_C( 59), UINT8_C( 27),
                             UINT8_C(131), UINT8_C(161), UINT8_C(251), UINT8_C(125),
                             UINT8_C(201), UINT8_C(252), UINT8_C(140), UINT8_C( 24),
                             UINT8_C(254), UINT8_C(183), UINT8_C(205), UINT8_C(238),
                             UINT8_C(180), UINT8_C( 21), UINT8_C( 59), UINT8_C(174)),
      simde_x_mm256_set_epu8(UINT8_C( 98), UINT8_C(152), UINT8_C(212), UINT8_C(148),
                             UINT8_C(183), UINT8_C( 37), UINT8_C(170), UINT8_C( 93),
                             UINT8_C( 52), UINT8_C(182), UINT8_C(181), UINT8_C(242),
                             UINT8_C(229), UINT8_C(182), UINT8_C(143), UINT8_C( 43),
                             UINT8_C(177), UINT8_C(115), UINT8_C(177), UINT8_C(170),
                             UINT8_C( 71), UINT8_C(222), UINT8_C(162), UINT8_C(198),
                             UINT8_C(195), UINT8_C(222), UINT8_C( 10), UINT8_C( 86),
                             UINT8_C( 48), UINT8_C(215), UINT8_C( 16), UINT8_C( 69)),
      simde_x_mm256_set_epu8(UINT8_C( 74), UINT8_C(143), UINT8_C( 19), UINT8_C(  8),
                             UINT8_C( 11), UINT8_C( 37), UINT8_C( 76), UINT8_C(  6),
                             UINT8_C( 52), UINT8_C( 67), UINT8_C(181), UINT8_C(163),
                             UINT8_C(113), UINT8_C(182), UINT8_C( 59), UINT8_C( 27),
                             UINT8_C(131), UINT8_C(115), UINT8_C(177), UINT8_C(125),
                             UINT8_C( 71), UINT8_C(222), UINT8_C(140), UINT8_C( 24),
                             UINT8_C(195), UINT8_C(183), UINT8_C( 10), UINT8_C( 86),
                             UINT8_C( 48), UINT8_C( 21), UINT8_C( 16), UINT8_C( 69)) },
    { simde_x_mm256_set_epu8(UINT8_C(119), UINT8_C(117), UINT8_C( 13), UINT8_C(207),
                             UINT8_C( 70), UINT8_C(197), UINT8_C(152), UINT8_C( 89),
                             UINT8_C(135), UINT8_C(159), UINT8_C( 50), UINT8_C(184),
                             UINT8_C(155), UINT8_C( 62), UINT8_C(253), UINT8_C(248),
                             UINT8_C(240), UINT8_C(207), UINT8_C( 53), UINT8_C(202),
                             UINT8_C(203), UINT8_C(241), UINT8_C(218), UINT8_C(118),
                             UINT8_C(121), UINT8_C(140), UINT8_C(125), UINT8_C( 65),
                             UINT8_C( 70), UINT8_C(249), UINT8_C(217), UINT8_C(237)),
      simde_x_mm256_set_epu8(UINT8_C(125), UINT8_C( 67), UINT8_C( 52), UINT8_C(  8),
                             UINT8_C(207), UINT8_C(205), UINT8_C( 56), UINT8_C(196),
                             UINT8_C( 42), UINT8_C(240), UINT8_C(116), UINT8_C( 44),
                             UINT8_C(109), UINT8_C(201), UINT8_C(220), UINT8_C(182),
                             UINT8_C(224), UINT8_C( 99), UINT8_C(151), UINT8_C(222),
                             UINT8_C(220), UINT8_C(252), UINT8_C(  6), UINT8_C(245),
                             UINT8_C(215), UINT8_C(221), UINT8_C(177), UINT8_C(240),
                             UINT8_C(118), UINT8_C(155), UINT8_C(143), UINT8_C(240)),
      simde_x_mm256_set_epu8(UINT8_C(119), UINT8_C( 67), UINT8_C( 13), UINT8_C(  8),
                             UINT8_C( 70), UINT8_C(197), UINT8_C( 56), UINT8_C( 89),
                             UINT8_C( 42), UINT8_C(159), UINT8_C( 50), UINT8_C( 44),
                             UINT8_C(109), UINT8_C( 62), UINT8_C(220), UINT8_C(182),
                             UINT8_C(224), UINT8_C( 99), UINT8_C( 53), UINT8_C(202),
                             UINT8_C(203), UINT8_C(241), UINT8_C(  6), UINT8_C(118),
                             UINT8_C(121), UINT8_C(140), UINT8_C(125), UINT8_C( 65),
                             UINT8_C( 70), UINT8_C(155), UINT8_C(143), UINT8_C(237)) },
    { simde_x_mm256_set_epu8(UINT8_C(201), UINT8_C(240), UINT8_C( 36), UINT8_C( 35),
                             UINT8_C(236), UINT8_C( 73), UINT8_C( 29), UINT8_C(244),
                             UINT8_C(140), UINT8_C( 36), UINT8_C(200), UINT8_C(155),
                             UINT8_C(  8), UINT8_C(245), UINT8_C( 10), UINT8_C( 93),
                             UINT8_C(124), UINT8_C(125), UINT8_C( 25), UINT8_C(192),
                             UINT8_C( 32), UINT8_C(119), UINT8_C(142), UINT8_C(147),
                             UINT8_C( 56), UINT8_C( 66), UINT8_C(172), UINT8_C(214),
                             UINT8_C(227), UINT8_C(203), UINT8_C( 62), UINT8_C( 37)),
      simde_x_mm256_set_epu8(UINT8_C(  5), UINT8_C( 64), UINT8_C(205), UINT8_C(118),
                             UINT8_C( 53), UINT8_C(  5), UINT8_C( 28), UINT8_C( 17),
                             UINT8_C( 93), UINT8_C(223), UINT8_C( 18), UINT8_C( 93),
                             UINT8_C(210), UINT8_C(158), UINT8_C( 37), UINT8_C( 66),
                             UINT8_C(184), UINT8_C(142), UINT8_C(246), UINT8_C( 15),
                             UINT8_C(153), UINT8_C(  9), UINT8_C(121), UINT8_C(211),
                             UINT8_C(  7), UINT8_C( 12), UINT8_C( 41), UINT8_C( 14),
                             UINT8_C(127), UINT8_C(208), UINT8_C(  7), UINT8_C( 93)),
      simde_x_mm256_set_epu8(UINT8_C(  5), UINT8_C( 64), UINT8_C( 36), UINT8_C( 35),
                             UINT8_C( 53), UINT8_C(  5), UINT8_C( 28), UINT8_C( 17),
                             UINT8_C( 93), UINT8_C( 36), UINT8_C( 18), UINT8_C( 93),
                             UINT8_C(  8), UINT8_C(158), UINT8_C( 10), UINT8_C( 66),
                             UINT8_C(124), UINT8_C(125), UINT8_C( 25), UINT8_C( 15),
                             UINT8_C( 32), UINT8_C(  9), UINT8_C(121), UINT8_C(147),
                             UINT8_C(  7), UINT8_C( 12), UINT8_C( 41), UINT8_C( 14),
                             UINT8_C(127), UINT8_C(203), UINT8_C(  7), UINT8_C( 37)) },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_min_epu8(test_vec[i].a, test_vec[i].b);
    simde_assert_m256i_u8(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_shuffle_epi8(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m256i a;
    simde__m256i b;
    simde__m256i r;
  } test_vec[8] = {
    { simde_x_mm256_set_epu8(UINT8_C(132), UINT8_C(100), UINT8_C(115), UINT8_C( 94),
                             UINT8_C( 73), UINT8_C(247), UINT8_C(104), UINT8_C(220),
                             UINT8_C(117), UINT8_C( 74), UINT8_C( 39), UINT8_C(125),
                             UINT8_C( 51), UINT8_C( 55), UINT8_C(148), UINT8_C(183),
                             UINT8_C(  5), UINT8_C(228), UINT8_C( 33), UINT8_C( 72),
                             UINT8_C( 84), UINT8_C(  4), UINT8_C(172), UINT8_C(134),
                             UINT8_C( 26), UINT8_C(247), UINT8_C(250), UINT8_C(  1),
                             UINT8_C(220), UINT8_C( 43), UINT8_C( 83), UINT8_C(118)),
      simde_x_mm256_set_epu8(UINT8_C( 24), UINT8_C(160), UINT8_C( 38), UINT8_C(201),
                             UINT8_C(108), UINT8_C( 32), UINT8_C( 93), UINT8_C( 16),
                             UINT8_C(104), UINT8_C(146), UINT8_C(128), UINT8_C(127),
                             UINT8_C(240), UINT8_C(187), UINT8_C(163), UINT8_C( 93),
                             UINT8_C(161), UINT8_C(148), UINT8_C(236), UINT8_C(208),
                             UINT8_C(110), UINT8_C( 19), UINT8_C(  3), UINT8_C(142),
                             UINT8_C( 56), UINT8_C( 74), UINT8_C(  2), UINT8_C(168),
                             UINT8_C(100), UINT8_C(209), UINT8_C( 27), UINT8_C( 46)),
      simde_x_mm256_set_epu8(UINT8_C(220), UINT8_C(  0), UINT8_C( 74), UINT8_C(  0),
                             UINT8_C( 94), UINT8_C(183), UINT8_C(115), UINT8_C(183),
                             UINT8_C(220), UINT8_C(  0), UINT8_C(  0), UINT8_C(132),
                             UINT8_C(  0), UINT8_C(  0), UINT8_C(  0), UINT8_C(115),
                             UINT8_C(  0), UINT8_C(  0), UINT8_C(  0), UINT8_C(  0),
                             UINT8_C(228), UINT8_C(220), UINT8_C(220), UINT8_C(  0),
                             UINT8_C(134), UINT8_C(  4), UINT8_C( 43), UINT8_C(  0),
                             UINT8_C(  1), UINT8_C(  0), UINT8_C( 84), UINT8_C(228)) },
    { simde_x_mm256_set_epu8(UINT8_C( 53), UINT8_C(227), UINT8_C(193), UINT8_C(203),
                             UINT8_C(188), UINT8_C( 31), UINT8_C(134), UINT8_C(151),
                             UINT8_C( 90), UINT8_C(227), UINT8_C(228), UINT8_C( 42),
                             UINT8_C(223), UINT8_C( 71), UINT8_C( 37), UINT8_C(166),
                             UINT8_C(115), UINT8_C( 13), UINT8_C(136), UINT8_C( 67),
                             UINT8_C(142), UINT8_C( 55), UINT8_C(218), UINT8_C(135),
                             UINT8_C(160), UINT8_C(121), UINT8_C(105), UINT8_C(225),
                             UINT8_C( 67), UINT8_C(106), UINT8_C( 80), UINT8_C(187)),
      simde_x_mm256_set_epu8(UINT8_C(139), UINT8_C(207), UINT8_C(188), UINT8_C(170),
                             UINT8_C(232), UINT8_C(172), UINT8_C( 51), UINT8_C( 14),
                             UINT8_C( 50), UINT8_C(186), UINT8_C( 76), UINT8_C(187),
                             UINT8_C( 22), UINT8_C( 90), UINT8_C(150), UINT8_C(148),
                             UINT8_C(123), UINT8_C( 36), UINT8_C(145), UINT8_C( 72),
                             UINT8_C(252), UINT8_C(171), UINT8_C(109), UINT8_C( 77),
                             UINT8_C(145), UINT8_C( 77), UINT8_C(121), UINT8_C(107),
                             UINT8_C(138), UINT8_C(154), UINT8_C(236), UINT8_C( 13)),
      simde_x_mm256_set_epu8(UINT8_C(  0), UINT8_C(  0), UINT8_C(  0), UINT8_C(  0),
                             UINT8_C(  0), UINT8_C(  0), UINT8_C(223), UINT8_C(227),
                             UINT8_C( 71), UINT8_C(  0), UINT8_C(203), UINT8_C(  0),
                             UINT8_C(227), UINT8_C( 31), UINT8_C(  0), UINT8_C(  0),
                             UINT8_C(142), UINT8_C(225), UINT8_C(  0), UINT8_C(135),
                             UINT8_C(  0), UINT8_C(  0), UINT8_C(136), UINT8_C(136),
                             UINT8_C(  0), UINT8_C(136), UINT8_C(218), UINT8_C(142),
                             UINT8_C(  0), UINT8_C(  0), UINT8_C(  0), UINT8_C(136)) },
    { simde_x_mm256_set_epu8(UINT8_C(147), UINT8_C(175), UINT8_C(103), UINT8_C(105),
                             UINT8_C(115), UINT8_C( 25), UINT8_C( 88), UINT8_C( 95),
                             UINT8_C(108), UINT8_C(195), UINT8_C( 30), UINT8_C( 32),
                             UINT8_C(183), UINT8_C(198), UINT8_C(177), UINT8_C( 61),
                             UINT8_C(213), UINT8_C(  7), UINT8_C(150), UINT8_C(186),
                             UINT8_C( 52), UINT8_C(  9), UINT8_C( 76), UINT8_C(240),
                             UINT8_C(240), UINT8_C(126), UINT8_C(242), UINT8_C(203),
                             UINT8_C(162), UINT8_C( 72), UINT8_C(186), UINT8_C( 35)),
      simde_x_mm256_set_epu8(UINT8_C( 26), UINT8_C(  1), UINT8_C(253), UINT8_C(220),
                             UINT8_C(156), UINT8_C(126), UINT8_C(237), UINT8_C(228),
                             UINT8_C(210), UINT8_C( 82), UINT8_C(  8), UINT8_C(  8),
                             UINT8_C(104), UINT8_C( 35), UINT8_C( 98), UINT8_C( 24),
                             UINT8_C(230), UINT8_C(227), UINT8_C( 73), UINT8_C(233),
                             UINT8_C(132), UINT8_C( 49), UINT8_C( 63), UINT8_C(172),
                             UINT8_C(137), UINT8_C( 87), UINT8_C( 85), UINT8_C(128),
                             UINT8_C(136), UINT8_C(108), UINT8_C( 70), UINT8_C(218)),
      simde_x_mm256_set_epu8(UINT8_C( 25), UINT8_C(177), UINT8_C(  0), UINT8_C(  0),
                             UINT8_C(  0), UINT8_C(175), UINT8_C(  0), UINT8_C(  0),
                             UINT8_C(  0), UINT8_C(198), UINT8_C( 95), UINT8_C( 95),
                             UINT8_C( 95), UINT8_C(183), UINT8_C(198), UINT8_C( 95),
                             UINT8_C(  0), UINT8_C(  0), UINT8_C( 76), UINT8_C(  0),
                             UINT8_C(  0), UINT8_C(186), UINT8_C(213), UINT8_C(  0),
                             UINT8_C(  0), UINT8_C(240), UINT8_C(242), UINT8_C(  0),
                             UINT8_C(  0), UINT8_C(186), UINT8_C(126), UINT8_C(  0)) },
    { simde_x_mm256_set_epu8(UINT8_C(132), UINT8_C( 22), UINT8_C(115), UINT8_C(245),
                             UINT8_C(139), UINT8_C(127), UINT8_C( 30), UINT8_C( 96),
                             UINT8_C(123), UINT8_C(228), UINT8_C( 73), UINT8_C(244),
                             UINT8_C( 12), UINT8_C( 46), UINT8_C( 26), UINT8_C( 36),
                             UINT8_C(186), UINT8_C( 18), UINT8_C(169), UINT8_C(233),
                             UINT8_C(  8), UINT8_C(185), UINT8_C(123), UINT8_C( 50),
                             UINT8_C(171), UINT8_C(240), UINT8_C(159), UINT8_C(176),
                             UINT8_C( 29), UINT8_C(146), UINT8_C( 85), UINT8_C( 34)),
      simde_x_mm256_set_epu8(UINT8_C(197), UINT8_C( 93), UINT8_C( 52), UINT8_C(130),
                             UINT8_C(124), UINT8_C( 87), UINT8_C( 88), UINT8_C( 89),
                             UINT8_C( 56), UINT8_C(209), UINT8_C( 85), UINT8_C(235),
                             UINT8_C( 45), UINT8_C(236), UINT8_C(154), UINT8_C( 72),
                             UINT8_C(164), UINT8_C(253), UINT8_C(196), UINT8_C( 41),
                             UINT8_C( 28), UINT8_C(181), UINT8_C(180), UINT8_C(237),
                             UINT8_C( 65), UINT8_C(122), UINT8_C(110), UINT8_C( 94),
                             UINT8_C(125), UINT8_C( 60), UINT8_C( 80), UINT8_C(209)),
      simde_x_mm256_set_epu8(UINT8_C(  0), UINT8_C(115), UINT8_C(244), UINT8_C(  0),
                             UINT8_C(245), UINT8_C(123), UINT8_C( 96), UINT8_C( 30),
                             UINT8_C( 96), UINT8_C(  0), UINT8_C( 73), UINT8_C(  0),
                             UINT8_C(115), UINT8_C(  0), UINT8_C(  0), UINT8_C( 96),
                             UINT8_C(  0), UINT8_C(  0), UINT8_C(  0), UINT8_C(123),
                             UINT8_C(233), UINT8_C(  0), UINT8_C(  0), UINT8_C(  0),
                             UINT8_C( 85), UINT8_C(185), UINT8_C( 18), UINT8_C( 18),
                             UINT8_C(169), UINT8_C(233), UINT8_C( 34), UINT8_C(  0)) },
    { simde_x_mm256_set_epu8(UINT8_C(233), UINT8_C(108), UINT8_C(215), UINT8_C(181),
                             UINT8_C(100), UINT8_C( 72), UINT8_C(220), UINT8_C( 52),
                             UINT8_C( 24), UINT8_C(  0), UINT8_C(242), UINT8_C(125),
                             UINT8_C(116), UINT8_C(102), UINT8_C( 94), UINT8_C( 64),
                             UINT8_C(158), UINT8_C(177), UINT8_C(  3), UINT8_C(246),
                             UINT8_C(164), UINT8_C(171), UINT8_C(138), UINT8_C( 15),
                             UINT8_C( 30), UINT8_C( 68), UINT8_C(246), UINT8_C(147),
                             UINT8_C(162), UINT8_C( 13), UINT8_C( 93), UINT8_C( 58)),
      simde_x_mm256_set_epu8(UINT8_C(159), UINT8_C(224), UINT8_C(140), UINT8_C(117),
                             UINT8_C( 95), UINT8_C( 45), UINT8_C(144), UINT8_C( 69),
                             UINT8_C(174), UINT8_C( 34), UINT8_C(237), UINT8_C( 42),
                             UINT8_C( 78), UINT8_C(  7), UINT8_C(200), UINT8_C(173),
                             UINT8_C(137), UINT8_C( 75), UINT8_C(170), UINT8_C(110),
                             UINT8_C(182), UINT8_C(180), UINT8_C(173), UINT8_C(172),
                             UINT8_C(227), UINT8_C(222), UINT8_C(132), UINT8_C(  4),
                             UINT8_C(190), UINT8_C(  7), UINT8_C( 12), UINT8_C( 21)),
      simde_x_mm256_set_epu8(UINT8_C(  0), UINT8_C(  0), UINT8_C(  0), UINT8_C(242),
                             UINT8_C(233), UINT8_C(215), UINT8_C(  0), UINT8_C(242),
                             UINT8_C(  0), UINT8_C(102), UINT8_C(  0), UINT8_C( 72),
                             UINT8_C(108), UINT8_C( 24), UINT8_C(  0), UINT8_C(  0),
                             UINT8_C(  0), UINT8_C(164), UINT8_C(  0), UINT8_C(177),
                             UINT8_C(  0), UINT8_C(  0), UINT8_C(  0), UINT8_C(  0),
                             UINT8_C(  0), UINT8_C(  0), UINT8_C(  0), UINT8_C(147),
                             UINT8_C(  0), UINT8_C( 30), UINT8_C(246), UINT8_C(246)) },
    { simde_x_mm256_set_epu8(UINT8_C(239), UINT8_C(190), UINT8_C( 67), UINT8_C(183),
                             UINT8_C(162), UINT8_C( 57), UINT8_C(249), UINT8_C(218),
                             UINT8_C(176), UINT8_C(139), UINT8_C(  3), UINT8_C(248),
                             UINT8_C(214), UINT8_C( 36), UINT8_C(105), UINT8_C( 96),
                             UINT8_C( 80), UINT8_C(108), UINT8_C(142), UINT8_C(  2),
                             UINT8_C(196), UINT8_C(162), UINT8_C( 38), UINT8_C(  4),
                             UINT8_C(175), UINT8_C(178), UINT8_C( 88), UINT8_C(165),
                             UINT8_C(168), UINT8_C( 71), UINT8_C( 76), UINT8_C(232)),
      simde_x_mm256_set_epu8(UINT8_C(199), UINT8_C( 95), UINT8_C( 43), UINT8_C(216),
                             UINT8_C(128), UINT8_C(137), UINT8_C(103), UINT8_C( 51),
                             UINT8_C(121), UINT8_C( 84), UINT8_C(196), UINT8_C(101),
                             UINT8_C(251), UINT8_C(  4), UINT8_C( 89), UINT8_C( 54),
                             UINT8_C(216), UINT8_C(149), UINT8_C(145), UINT8_C( 73),
                             UINT8_C(162), UINT8_C( 73), UINT8_C(124), UINT8_C(146),
                             UINT8_C( 70), UINT8_C(151), UINT8_C(137), UINT8_C(218),
                             UINT8_C(230), UINT8_C(112), UINT8_C( 45), UINT8_C(226)),
      simde_x_mm256_set_epu8(UINT8_C(  0), UINT8_C(239), UINT8_C(162), UINT8_C(  0),
                             UINT8_C(  0), UINT8_C(  0), UINT8_C(176), UINT8_C(214),
                             UINT8_C(249), UINT8_C(248), UINT8_C(  0), UINT8_C(  3),
                             UINT8_C(  0), UINT8_C(248), UINT8_C(249), UINT8_C(139),
                             UINT8_C(  0), UINT8_C(  0), UINT8_C(  0), UINT8_C( 38),
                             UINT8_C(  0), UINT8_C( 38), UINT8_C(  2), UINT8_C(  0),
                             UINT8_C(178), UINT8_C(  0), UINT8_C(  0), UINT8_C(  0),
                             UINT8_C(  0), UINT8_C(232), UINT8_C(142), UINT8_C(  0)) },
    { simde_x_mm256_set_epu8(UINT8_C( 81), UINT8_C(102), UINT8_C( 49), UINT8_C(133),
                             UINT8_C(250), UINT8_C( 13), UINT8_C(233), UINT8_C( 67),
                             UINT8_C(205), UINT8_C(254), UINT8_C( 41), UINT8_C(  6),
                             UINT8_C(117), UINT8_C(148), UINT8_C(222), UINT8_C(171),
                             UINT8_C(  8), UINT8_C( 99), UINT8_C( 93), UINT8_C( 39),
                             UINT8_C(103), UINT8_C(215), UINT8_C(216), UINT8_C( 75),
                             UINT8_C( 94), UINT8_C(171), UINT8_C( 41), UINT8_C(173),
                             UINT8_C(217), UINT8_C(138), UINT8_C(180), UINT8_C(160)),
      simde_x_mm256_set_epu8(UINT8_C(200), UINT8_C(107), UINT8_C(119), UINT8_C(216),
                             UINT8_C( 73), UINT8_C(187), UINT8_C(212), UINT8_C( 20),
                             UINT8_C( 22), UINT8_C( 11), UINT8_C(155), UINT8_C(106),
                             UINT8_C( 35), UINT8_C(108), UINT8_C( 43), UINT8_C( 58),
                             UINT8_C(102), UINT8_C(228), UINT8_C(  5), UINT8_C(227),
                             UINT8_C(106), UINT8_C(119), UINT8_C(184), UINT8_C(199),
                             UINT8_C( 57), UINT8_C(120), UINT8_C( 14), UINT8_C( 56),
                             UINT8_C( 82), UINT8_C( 19), UINT8_C( 33), UINT8_C( 82)),
      simde_x_mm256_set_epu8(UINT8_C(  0), UINT8_C(250), UINT8_C(205), UINT8_C(  0),
                             UINT8_C(233), UINT8_C(  0), UINT8_C(  0), UINT8_C(  6),
                             UINT8_C(254), UINT8_C(250), UINT8_C(  0), UINT8_C( 13),
                             UINT8_C(117), UINT8_C(133), UINT8_C(250), UINT8_C( 13),
                             UINT8_C(171), UINT8_C(  0), UINT8_C( 41), UINT8_C(  0),
                             UINT8_C(215), UINT8_C( 94), UINT8_C(  0), UINT8_C(  0),
                             UINT8_C(216), UINT8_C( 75), UINT8_C( 99), UINT8_C( 75),
                             UINT8_C(138), UINT8_C(217), UINT8_C(180), UINT8_C(138)) },
    { simde_x_mm256_set_epu8(UINT8_C(173), UINT8_C(218), UINT8_C( 20), UINT8_C( 45),
                             UINT8_C(110), UINT8_C( 90), UINT8_C(183), UINT8_C( 54),
                             UINT8_C(102), UINT8_C(126), UINT8_C(167), UINT8_C(135),
                             UINT8_C( 42), UINT8_C( 74), UINT8_C( 22), UINT8_C(137),
                             UINT8_C( 56), UINT8_C(  5), UINT8_C( 18), UINT8_C(105),
                             UINT8_C( 83), UINT8_C(146), UINT8_C(229), UINT8_C( 54),
                             UINT8_C(169), UINT8_C( 55), UINT8_C(228), UINT8_C(168),
                             UINT8_C(  1), UINT8_C(126), UINT8_C(169), UINT8_C(235)),
      simde_x_mm256_set_epu8(UINT8_C(254), UINT8_C( 56), UINT8_C(  4), UINT8_C(163),
                             UINT8_C( 35), UINT8_C( 52), UINT8_C(182), UINT8_C( 52),
                             UINT8_C(  1), UINT8_C( 45), UINT8_C(119), UINT8_C(169),
                             UINT8_C(175), UINT8_C(254), UINT8_C( 71), UINT8_C( 63),
                             UINT8_C( 24), UINT8_C(116), UINT8_C(194), UINT8_C(184),
                             UINT8_C(150), UINT8_C(167), UINT8_C(101), UINT8_C(133),
                             UINT8_C( 95), UINT8_C( 84), UINT8_C(199), UINT8_C(134),
                             UINT8_C(251), UINT8_C(101), UINT8_C( 38), UINT8_C( 43)),
      simde_x_mm256_set_epu8(UINT8_C(  0), UINT8_C( 54), UINT8_C(135), UINT8_C(  0),
                             UINT8_C( 42), UINT8_C(135), UINT8_C(  0), UINT8_C(135),
                             UINT8_C( 22), UINT8_C( 20), UINT8_C(102), UINT8_C(  0),
                             UINT8_C(  0), UINT8_C(  0), UINT8_C(102), UINT8_C(173),
                             UINT8_C( 54), UINT8_C(168), UINT8_C(  0), UINT8_C(  0),
                             UINT8_C(  0), UINT8_C(  0), UINT8_C(228), UINT8_C(  0),
                             UINT8_C( 56), UINT8_C(168), UINT8_C(  0), UINT8_C(  0),
                             UINT8_C(  0), UINT8_C(228), UINT8_C( 55), UINT8_C( 83)) }
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_shuffle_epi8(test_vec[i].a, test_vec[i].b);
    simde_assert_m256i_u8(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_slli_epi32(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m256i a;
    simde__m256i r;
  } test_vec[8] = {
    { simde_mm256_set_epi32(INT32_C(   94292442), INT32_C(-1628389608), INT32_C(-1024206707), INT32_C(  523710922),
                            INT32_C(  978667586), INT32_C( 1659490027), INT32_C(-1334188807), INT32_C( 1260021436)),
      simde_mm256_set_epi32(INT32_C(-1277609152), INT32_C( -568859904), INT32_C( 1585123744), INT32_C( -421119680),
                            INT32_C( 1252591680), INT32_C( 1564073312), INT32_C(  255631136), INT32_C( 1665980288)) },
    { simde_mm256_set_epi32(INT32_C(  672859837), INT32_C(  342764531), INT32_C(-1803807158), INT32_C( -451944397),
                            INT32_C( 1870966936), INT32_C(  186604480), INT32_C( 1887886881), INT32_C( -855965708)),
      simde_mm256_set_epi32(INT32_C(   56678304), INT32_C(-1916436896), INT32_C(-1887254208), INT32_C(-1577318816),
                            INT32_C( -258600192), INT32_C( 1676376064), INT32_C(  282838048), INT32_C(-1621098880)) },
    { simde_mm256_set_epi32(INT32_C( -975940222), INT32_C(  871174230), INT32_C(-1409369958), INT32_C( 1678365182),
                            INT32_C( 1297931630), INT32_C( -258078693), INT32_C(   54773518), INT32_C(-1666795964)),
      simde_mm256_set_epi32(INT32_C(-1165316032), INT32_C( 2107771584), INT32_C( 2144801600), INT32_C(-2126889024),
                            INT32_C(-1415860800), INT32_C(  331416416), INT32_C( 1752752576), INT32_C(-1797863296)) },
    { simde_mm256_set_epi32(INT32_C(-2146769442), INT32_C( -589676138), INT32_C(  818134583), INT32_C( -705230189),
                            INT32_C( 1091476596), INT32_C( -599903650), INT32_C(-2028456506), INT32_C( -592435270)),
      simde_mm256_set_epi32(INT32_C(   22854592), INT32_C(-1689767232), INT32_C(  410502880), INT32_C(-1092529568),
                            INT32_C(  567512704), INT32_C(-2017047616), INT32_C( -486098752), INT32_C(-1778059456)) },
    { simde_mm256_set_epi32(INT32_C( -375868530), INT32_C(-1215336020), INT32_C( -787206751), INT32_C( -493138836),
                            INT32_C( 1146700163), INT32_C(    6578381), INT32_C(  359632137), INT32_C(-2113779494)),
      simde_mm256_set_epi32(INT32_C(  857108928), INT32_C( -236046976), INT32_C(  579187744), INT32_C( 1399426432),
                            INT32_C(-1960300448), INT32_C(  210508192), INT32_C(-1376673504), INT32_C( 1078532928)) },
    { simde_mm256_set_epi32(INT32_C( -880661140), INT32_C(  791300264), INT32_C(  518403119), INT32_C( 1471222669),
                            INT32_C(-1540031073), INT32_C(-1046150587), INT32_C(  301144597), INT32_C( 1823741999)),
      simde_mm256_set_epi32(INT32_C( 1883614592), INT32_C( -448195328), INT32_C( -590969376), INT32_C( -165514848),
                            INT32_C(-2036354080), INT32_C(  882919584), INT32_C( 1046692512), INT32_C(-1769798176)) },
    { simde_mm256_set_epi32(INT32_C( 1562915995), INT32_C(-1381854677), INT32_C( 1716471903), INT32_C( -741647744),
                            INT32_C( -832333591), INT32_C( 1483182880), INT32_C(  845074829), INT32_C(-1923440996)),
      simde_mm256_set_epi32(INT32_C(-1526295712), INT32_C(-1269676704), INT32_C( -907473952), INT32_C( 2037075968),
                            INT32_C( -864871136), INT32_C(  217211904), INT32_C( 1272590752), INT32_C(-1420569728)) },
    { simde_mm256_set_epi32(INT32_C(-2071181413), INT32_C(  141896408), INT32_C(  388952698), INT32_C( 1988301650),
                            INT32_C(  268230479), INT32_C(  996155067), INT32_C(   -1277500), INT32_C(-1381446832)),
      simde_mm256_set_epi32(INT32_C(-1853295776), INT32_C(  245717760), INT32_C( -438415552), INT32_C( -798856640),
                            INT32_C(   -6559264), INT32_C( 1812191072), INT32_C(  -40880000), INT32_C(-1256625664)) },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_slli_epi32(test_vec[i].a, 5);
    simde_assert_m256i_i32(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_srli_epi64(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m256i a;
    simde__m256i r;
  } test_vec[8] = {
    { simde_mm256_set_epi64x(INT64_C(-4256718216449012213), INT64_C( 6954428280967509650),
                             INT64_C( 1187214080985021589), INT64_C(-4702330273301320405)),
      simde_mm256_set_epi64x(INT64_C(    1732180890778874), INT64_C(     848929233516541),
                             INT64_C(     144923593870241), INT64_C(    1677784887745145)) },
    { simde_mm256_set_epi64x(INT64_C(-3743076857167596375), INT64_C(-2949526633471503649),
                             INT64_C( -669110663294743741), INT64_C( 7371470111003579569)),
      simde_mm256_set_epi64x(INT64_C(    1794881252019281), INT64_C(    1891750175810308),
                             INT64_C(    2170121265919776), INT64_C(     899837660034616)) },
    { simde_mm256_set_epi64x(INT64_C(-1169177286944430348), INT64_C( 6455539972528691466),
                             INT64_C(-3144731664245862155), INT64_C( 8588725191818949696)),
      simde_mm256_set_epi64x(INT64_C(    2109077976900039), INT64_C(     788029781802818),
                             INT64_C(    1867921436702110), INT64_C(    1048428368141961)) },
    { simde_mm256_set_epi64x(INT64_C( 5021751163006482875), INT64_C( 2964602111576624904),
                             INT64_C(-4368546882672922616), INT64_C(-5401573381584498754)),
      simde_mm256_set_epi64x(INT64_C(     613006733765439), INT64_C(     361889906198318),
                             INT64_C(    1718529930546463), INT64_C(    1592428063003546)) },
    { simde_mm256_set_epi64x(INT64_C( 3259692229419136160), INT64_C( 7535593008241291393),
                             INT64_C( 5636342892427003163), INT64_C(-1571672726362789760)),
      simde_mm256_set_epi64x(INT64_C(     397911649099015), INT64_C(     919872193388829),
                             INT64_C(     688030138235718), INT64_C(    2059945232830415)) },
    { simde_mm256_set_epi64x(INT64_C(  989750983639101530), INT64_C( 8678458181172187091),
                             INT64_C(-2685498580325005795), INT64_C( 3115460859126861666)),
      simde_mm256_set_epi64x(INT64_C(     120819211870007), INT64_C(    1059382102193870),
                             INT64_C(    1923980162766668), INT64_C(     380305280655134)) },
    { simde_mm256_set_epi64x(INT64_C( 4213211340014625996), INT64_C( 2088661399522998885),
                             INT64_C( 8429870025320256082), INT64_C( 3926130149086841056)),
      simde_mm256_set_epi64x(INT64_C(     514308024904129), INT64_C(     254963549746459),
                             INT64_C(    1029036868325226), INT64_C(     479263934214702)) },
    { simde_mm256_set_epi64x(INT64_C(-1914589078060239315), INT64_C(-3242383134288733864),
                             INT64_C( 7743081591170414486), INT64_C( 6381904702631892778)),
      simde_mm256_set_epi64x(INT64_C(    2018085326617347), INT64_C(    1856001091237892),
                             INT64_C(     945200389547169), INT64_C(     779041101395494)) }
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_srli_epi64(test_vec[i].a, 13);
    simde_assert_m256i_i64(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_sub_epi8(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m256i a;
    simde__m256i b;
    simde__m256i r;
  } test_vec[8] = {
   { simde_mm256_set_epi8(INT8_C( -37), INT8_C(  -5), INT8_C( -23), INT8_C(  84),
                           INT8_C(-108), INT8_C( -92), INT8_C(  86), INT8_C( -77),
                           INT8_C(  77), INT8_C( -93), INT8_C( -37), INT8_C( 101),
                           INT8_C(  79), INT8_C( -45), INT8_C(  56), INT8_C( -51),
                           INT8_C( 103), INT8_C(-116), INT8_C( -58), INT8_C(  -2),
                           INT8_C(  39), INT8_C(-101), INT8_C(-113), INT8_C(  21),
                           INT8_C( -77), INT8_C(  26), INT8_C( -37), INT8_C( 126),
                           INT8_C( 102), INT8_C(  27), INT8_C( -92), INT8_C( -33)),
      simde_mm256_set_epi8(INT8_C(-122), INT8_C( -91), INT8_C(  24), INT8_C(-103),
                           INT8_C(  34), INT8_C(   5), INT8_C( 109), INT8_C(-120),
                           INT8_C(  -7), INT8_C(  86), INT8_C(   3), INT8_C(  90),
                           INT8_C(  98), INT8_C(-108), INT8_C(-128), INT8_C(  33),
                           INT8_C( -84), INT8_C( -73), INT8_C( -39), INT8_C(  33),
                           INT8_C( 103), INT8_C( -21), INT8_C(-117), INT8_C( -60),
                           INT8_C( -48), INT8_C( -88), INT8_C(  95), INT8_C( 100),
                           INT8_C( -66), INT8_C(  52), INT8_C( -40), INT8_C(  90)),
      simde_mm256_set_epi8(INT8_C(  85), INT8_C(  86), INT8_C( -47), INT8_C( -69),
                           INT8_C( 114), INT8_C( -97), INT8_C( -23), INT8_C(  43),
                           INT8_C(  84), INT8_C(  77), INT8_C( -40), INT8_C(  11),
                           INT8_C( -19), INT8_C(  63), INT8_C( -72), INT8_C( -84),
                           INT8_C( -69), INT8_C( -43), INT8_C( -19), INT8_C( -35),
                           INT8_C( -64), INT8_C( -80), INT8_C(   4), INT8_C(  81),
                           INT8_C( -29), INT8_C( 114), INT8_C( 124), INT8_C(  26),
                           INT8_C( -88), INT8_C( -25), INT8_C( -52), INT8_C(-123)) },
    { simde_mm256_set_epi8(INT8_C( -74), INT8_C( -43), INT8_C( -65), INT8_C(  71),
                           INT8_C(-122), INT8_C(-128), INT8_C(   4), INT8_C(  54),
                           INT8_C(  12), INT8_C(  60), INT8_C(  80), INT8_C( -43),
                           INT8_C( -85), INT8_C(  94), INT8_C( -70), INT8_C(  67),
                           INT8_C(  82), INT8_C(  40), INT8_C( -92), INT8_C( -55),
                           INT8_C( 114), INT8_C(  12), INT8_C( -43), INT8_C( -93),
                           INT8_C( -89), INT8_C( -90), INT8_C(  46), INT8_C( -34),
                           INT8_C( -53), INT8_C(   0), INT8_C(  91), INT8_C( -43)),
      simde_mm256_set_epi8(INT8_C(  34), INT8_C( -42), INT8_C(  32), INT8_C( -31),
                           INT8_C( 117), INT8_C( -44), INT8_C( 116), INT8_C( -46),
                           INT8_C( 114), INT8_C(  78), INT8_C(  -3), INT8_C( 123),
                           INT8_C( 103), INT8_C(   4), INT8_C( -99), INT8_C(-112),
                           INT8_C(  67), INT8_C(-113), INT8_C(  -1), INT8_C(-117),
                           INT8_C( -58), INT8_C( -63), INT8_C(-110), INT8_C(  65),
                           INT8_C(  53), INT8_C(-113), INT8_C(-123), INT8_C( -24),
                           INT8_C( -84), INT8_C( -96), INT8_C( 116), INT8_C(  23)),
      simde_mm256_set_epi8(INT8_C(-108), INT8_C(  -1), INT8_C( -97), INT8_C( 102),
                           INT8_C(  17), INT8_C( -84), INT8_C(-112), INT8_C( 100),
                           INT8_C(-102), INT8_C( -18), INT8_C(  83), INT8_C(  90),
                           INT8_C(  68), INT8_C(  90), INT8_C(  29), INT8_C( -77),
                           INT8_C(  15), INT8_C(-103), INT8_C( -91), INT8_C(  62),
                           INT8_C( -84), INT8_C(  75), INT8_C(  67), INT8_C(  98),
                           INT8_C( 114), INT8_C(  23), INT8_C( -87), INT8_C( -10),
                           INT8_C(  31), INT8_C(  96), INT8_C( -25), INT8_C( -66)) },
    { simde_mm256_set_epi8(INT8_C( -56), INT8_C( -54), INT8_C( -84), INT8_C( -79),
                           INT8_C(  25), INT8_C( -22), INT8_C( -93), INT8_C( -71),
                           INT8_C(-106), INT8_C(-125), INT8_C( -67), INT8_C(  53),
                           INT8_C( 101), INT8_C(-105), INT8_C( -28), INT8_C(  37),
                           INT8_C( -61), INT8_C( -39), INT8_C(-117), INT8_C(-116),
                           INT8_C( -16), INT8_C(-126), INT8_C(  25), INT8_C( 103),
                           INT8_C( -81), INT8_C(  88), INT8_C(   1), INT8_C(  20),
                           INT8_C(  36), INT8_C(  16), INT8_C( -44), INT8_C( 107)),
      simde_mm256_set_epi8(INT8_C(  73), INT8_C(-125), INT8_C(  72), INT8_C(  17),
                           INT8_C( -36), INT8_C(  20), INT8_C( -81), INT8_C(  10),
                           INT8_C( 119), INT8_C(  41), INT8_C( -90), INT8_C( -54),
                           INT8_C(-116), INT8_C(  15), INT8_C( -64), INT8_C(  60),
                           INT8_C( -43), INT8_C(   5), INT8_C(  93), INT8_C(  54),
                           INT8_C( -46), INT8_C(-106), INT8_C(-117), INT8_C( 127),
                           INT8_C(  81), INT8_C( -75), INT8_C(-105), INT8_C(  31),
                           INT8_C(  51), INT8_C(-105), INT8_C( -23), INT8_C(  95)),
      simde_mm256_set_epi8(INT8_C( 127), INT8_C(  71), INT8_C( 100), INT8_C( -96),
                           INT8_C(  61), INT8_C( -42), INT8_C( -12), INT8_C( -81),
                           INT8_C(  31), INT8_C(  90), INT8_C(  23), INT8_C( 107),
                           INT8_C( -39), INT8_C(-120), INT8_C(  36), INT8_C( -23),
                           INT8_C( -18), INT8_C( -44), INT8_C(  46), INT8_C(  86),
                           INT8_C(  30), INT8_C( -20), INT8_C(-114), INT8_C( -24),
                           INT8_C(  94), INT8_C( -93), INT8_C( 106), INT8_C( -11),
                           INT8_C( -15), INT8_C( 121), INT8_C( -21), INT8_C(  12)) },
    { simde_mm256_set_epi8(INT8_C( 114), INT8_C(  34), INT8_C(  26), INT8_C( -19),
                           INT8_C( -79), INT8_C( -66), INT8_C( -16), INT8_C(  14),
                           INT8_C(-119), INT8_C(  36), INT8_C(  48), INT8_C(-124),
                           INT8_C(  -3), INT8_C(  65), INT8_C(  48), INT8_C(-117),
                           INT8_C( -76), INT8_C( -16), INT8_C(  83), INT8_C(   8),
                           INT8_C(  76), INT8_C( -37), INT8_C( -88), INT8_C( -95),
                           INT8_C( -96), INT8_C(  84), INT8_C(  -4), INT8_C(  56),
                           INT8_C(  13), INT8_C( -84), INT8_C( 107), INT8_C( -97)),
      simde_mm256_set_epi8(INT8_C(-116), INT8_C( -40), INT8_C( 117), INT8_C(  -7),
                           INT8_C( -80), INT8_C(  53), INT8_C( -24), INT8_C(-123),
                           INT8_C(-119), INT8_C( -47), INT8_C( -64), INT8_C( -25),
                           INT8_C( 117), INT8_C(  45), INT8_C(  40), INT8_C( -91),
                           INT8_C(  19), INT8_C( 123), INT8_C(  36), INT8_C(  -6),
                           INT8_C(  29), INT8_C(  -9), INT8_C( 117), INT8_C( -17),
                           INT8_C( -12), INT8_C(  82), INT8_C( 121), INT8_C(   9),
                           INT8_C( -40), INT8_C(-118), INT8_C( -50), INT8_C( -94)),
      simde_mm256_set_epi8(INT8_C( -26), INT8_C(  74), INT8_C( -91), INT8_C( -12),
                           INT8_C(   1), INT8_C(-119), INT8_C(   8), INT8_C(-119),
                           INT8_C(   0), INT8_C(  83), INT8_C( 112), INT8_C( -99),
                           INT8_C(-120), INT8_C(  20), INT8_C(   8), INT8_C( -26),
                           INT8_C( -95), INT8_C( 117), INT8_C(  47), INT8_C(  14),
                           INT8_C(  47), INT8_C( -28), INT8_C(  51), INT8_C( -78),
                           INT8_C( -84), INT8_C(   2), INT8_C(-125), INT8_C(  47),
                           INT8_C(  53), INT8_C(  34), INT8_C( -99), INT8_C(  -3)) },
    { simde_mm256_set_epi8(INT8_C(  95), INT8_C( -54), INT8_C(  -5), INT8_C( -28),
                           INT8_C( -63), INT8_C(  54), INT8_C(-113), INT8_C( 127),
                           INT8_C( -25), INT8_C( -12), INT8_C(-108), INT8_C(-123),
                           INT8_C( -64), INT8_C(  68), INT8_C(  89), INT8_C(  72),
                           INT8_C( -46), INT8_C( -63), INT8_C(  56), INT8_C( 125),
                           INT8_C(  44), INT8_C(   8), INT8_C(  49), INT8_C( 105),
                           INT8_C(  43), INT8_C(  41), INT8_C( -46), INT8_C(-117),
                           INT8_C(  22), INT8_C(  27), INT8_C( -55), INT8_C( 106)),
      simde_mm256_set_epi8(INT8_C(  15), INT8_C( -64), INT8_C(   3), INT8_C( -17),
                           INT8_C( 127), INT8_C(-101), INT8_C(  76), INT8_C(  31),
                           INT8_C(  79), INT8_C( 115), INT8_C( -72), INT8_C( -19),
                           INT8_C(-105), INT8_C( 117), INT8_C( -69), INT8_C(  62),
                           INT8_C(  51), INT8_C( -12), INT8_C( -69), INT8_C(-109),
                           INT8_C(-101), INT8_C( -50), INT8_C(  90), INT8_C(  52),
                           INT8_C(  58), INT8_C( -94), INT8_C( -69), INT8_C(  88),
                           INT8_C(  -9), INT8_C(  25), INT8_C(  89), INT8_C(  31)),
      simde_mm256_set_epi8(INT8_C(  80), INT8_C(  10), INT8_C(  -8), INT8_C( -11),
                           INT8_C(  66), INT8_C(-101), INT8_C(  67), INT8_C(  96),
                           INT8_C(-104), INT8_C(-127), INT8_C( -36), INT8_C(-104),
                           INT8_C(  41), INT8_C( -49), INT8_C( -98), INT8_C(  10),
                           INT8_C( -97), INT8_C( -51), INT8_C( 125), INT8_C( -22),
                           INT8_C(-111), INT8_C(  58), INT8_C( -41), INT8_C(  53),
                           INT8_C( -15), INT8_C(-121), INT8_C(  23), INT8_C(  51),
                           INT8_C(  31), INT8_C(   2), INT8_C( 112), INT8_C(  75)) },
    { simde_mm256_set_epi8(INT8_C(  58), INT8_C( -35), INT8_C(  -9), INT8_C( -15),
                           INT8_C( -74), INT8_C( -92), INT8_C( -26), INT8_C( -48),
                           INT8_C( -14), INT8_C(  54), INT8_C(  39), INT8_C( 120),
                           INT8_C( -38), INT8_C( -90), INT8_C( 101), INT8_C(  25),
                           INT8_C(  90), INT8_C( 106), INT8_C(  24), INT8_C( -31),
                           INT8_C( -57), INT8_C(   7), INT8_C(  29), INT8_C( 106),
                           INT8_C( 124), INT8_C(  62), INT8_C(  44), INT8_C(  40),
                           INT8_C(  54), INT8_C(  54), INT8_C( -93), INT8_C( -77)),
      simde_mm256_set_epi8(INT8_C(  65), INT8_C(-103), INT8_C(  10), INT8_C( 103),
                           INT8_C(  65), INT8_C(  90), INT8_C( -56), INT8_C(  98),
                           INT8_C(  64), INT8_C( 110), INT8_C( -94), INT8_C(  23),
                           INT8_C( -62), INT8_C(  19), INT8_C( 115), INT8_C(  93),
                           INT8_C(  68), INT8_C(  91), INT8_C(  -1), INT8_C(   5),
                           INT8_C(  19), INT8_C( -54), INT8_C( -79), INT8_C(-124),
                           INT8_C( -14), INT8_C( 106), INT8_C( -71), INT8_C( -34),
                           INT8_C(  39), INT8_C( -20), INT8_C( 117), INT8_C( -23)),
      simde_mm256_set_epi8(INT8_C(  -7), INT8_C(  68), INT8_C( -19), INT8_C(-118),
                           INT8_C( 117), INT8_C(  74), INT8_C(  30), INT8_C( 110),
                           INT8_C( -78), INT8_C( -56), INT8_C(-123), INT8_C(  97),
                           INT8_C(  24), INT8_C(-109), INT8_C( -14), INT8_C( -68),
                           INT8_C(  22), INT8_C(  15), INT8_C(  25), INT8_C( -36),
                           INT8_C( -76), INT8_C(  61), INT8_C( 108), INT8_C( -26),
                           INT8_C(-118), INT8_C( -44), INT8_C( 115), INT8_C(  74),
                           INT8_C(  15), INT8_C(  74), INT8_C(  46), INT8_C( -54)) },
    { simde_mm256_set_epi8(INT8_C( -10), INT8_C(  24), INT8_C(-113), INT8_C( -36),
                           INT8_C( 115), INT8_C(  49), INT8_C(  18), INT8_C(  86),
                           INT8_C( 112), INT8_C(  85), INT8_C( -24), INT8_C( -37),
                           INT8_C( -39), INT8_C(  13), INT8_C(   8), INT8_C(  92),
                           INT8_C( -95), INT8_C(-112), INT8_C(  83), INT8_C(  16),
                           INT8_C( 106), INT8_C(-127), INT8_C( 122), INT8_C( -83),
                           INT8_C( -96), INT8_C( -94), INT8_C(  86), INT8_C( -10),
                           INT8_C( -44), INT8_C( -36), INT8_C(  93), INT8_C(  71)),
      simde_mm256_set_epi8(INT8_C( -12), INT8_C(-115), INT8_C( 101), INT8_C( -47),
                           INT8_C(  85), INT8_C( -78), INT8_C( -44), INT8_C(  16),
                           INT8_C(  71), INT8_C(   4), INT8_C( -58), INT8_C(   7),
                           INT8_C(  30), INT8_C(  54), INT8_C(  60), INT8_C(  -1),
                           INT8_C( -73), INT8_C( -28), INT8_C( -92), INT8_C( -36),
                           INT8_C(  82), INT8_C( -11), INT8_C( -69), INT8_C(   2),
                           INT8_C( -76), INT8_C( 100), INT8_C(  99), INT8_C(   0),
                           INT8_C( -87), INT8_C( -70), INT8_C(  29), INT8_C( 121)),
      simde_mm256_set_epi8(INT8_C(   2), INT8_C(-117), INT8_C(  42), INT8_C(  11),
                           INT8_C(  30), INT8_C( 127), INT8_C(  62), INT8_C(  70),
                           INT8_C(  41), INT8_C(  81), INT8_C(  34), INT8_C( -44),
                           INT8_C( -69), INT8_C( -41), INT8_C( -52), INT8_C(  93),
                           INT8_C( -22), INT8_C( -84), INT8_C( -81), INT8_C(  52),
                           INT8_C(  24), INT8_C(-116), INT8_C( -65), INT8_C( -85),
                           INT8_C( -20), INT8_C(  62), INT8_C( -13), INT8_C( -10),
                           INT8_C(  43), INT8_C(  34), INT8_C(  64), INT8_C( -50)) },
    { simde_mm256_set_epi8(INT8_C(   2), INT8_C( -33), INT8_C(  21), INT8_C(  39),
                           INT8_C(  -5), INT8_C(-110), INT8_C(-113), INT8_C(  98),
                           INT8_C(   6), INT8_C(  47), INT8_C( -26), INT8_C(  73),
                           INT8_C(-121), INT8_C( -53), INT8_C( 102), INT8_C( 110),
                           INT8_C( -38), INT8_C( -97), INT8_C( -70), INT8_C(-105),
                           INT8_C(-128), INT8_C(  48), INT8_C( -78), INT8_C( 108),
                           INT8_C( 118), INT8_C(   9), INT8_C(  40), INT8_C( 110),
                           INT8_C( -32), INT8_C( -25), INT8_C(  39), INT8_C(-123)),
      simde_mm256_set_epi8(INT8_C(  15), INT8_C(  27), INT8_C(  -7), INT8_C(-103),
                           INT8_C(  81), INT8_C( 127), INT8_C( -25), INT8_C(  51),
                           INT8_C( -31), INT8_C(  28), INT8_C(-102), INT8_C(  24),
                           INT8_C(  73), INT8_C( 119), INT8_C( 106), INT8_C(   1),
                           INT8_C(   5), INT8_C(-108), INT8_C( -84), INT8_C(  54),
                           INT8_C( -30), INT8_C(-120), INT8_C(  39), INT8_C(   6),
                           INT8_C(-115), INT8_C(-128), INT8_C( 110), INT8_C(  39),
                           INT8_C(-110), INT8_C(-102), INT8_C(   6), INT8_C( 126)),
      simde_mm256_set_epi8(INT8_C( -13), INT8_C( -60), INT8_C(  28), INT8_C(-114),
                           INT8_C( -86), INT8_C(  19), INT8_C( -88), INT8_C(  47),
                           INT8_C(  37), INT8_C(  19), INT8_C(  76), INT8_C(  49),
                           INT8_C(  62), INT8_C(  84), INT8_C(  -4), INT8_C( 109),
                           INT8_C( -43), INT8_C(  11), INT8_C(  14), INT8_C(  97),
                           INT8_C( -98), INT8_C( -88), INT8_C(-117), INT8_C( 102),
                           INT8_C( -23), INT8_C(-119), INT8_C( -70), INT8_C(  71),
                           INT8_C(  78), INT8_C(  77), INT8_C(  33), INT8_C(   7)) },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_sub_epi8(test_vec[i].a, test_vec[i].b);
    simde_assert_m256i_i8(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_sub_epi16(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m256i a;
    simde__m256i b;
    simde__m256i r;
  } test_vec[8] = {
   { simde_mm256_set_epi16(INT16_C(-27953), INT16_C(-25893), INT16_C( 18102), INT16_C( -6593),
                            INT16_C(  7623), INT16_C( 27326), INT16_C(-15847), INT16_C( 25196),
                            INT16_C(  4150), INT16_C( 31494), INT16_C( 14922), INT16_C(  2426),
                            INT16_C(  8906), INT16_C( -8618), INT16_C(-26305), INT16_C(  2552)),
      simde_mm256_set_epi16(INT16_C(-20113), INT16_C( 26325), INT16_C( 23863), INT16_C(-13511),
                            INT16_C(  6653), INT16_C( 22833), INT16_C( 26506), INT16_C( 21325),
                            INT16_C(-18785), INT16_C( -8308), INT16_C( -2522), INT16_C(   805),
                            INT16_C(-27299), INT16_C( 31631), INT16_C( -9722), INT16_C(  3708)),
      simde_mm256_set_epi16(INT16_C( -7840), INT16_C( 13318), INT16_C( -5761), INT16_C(  6918),
                            INT16_C(   970), INT16_C(  4493), INT16_C( 23183), INT16_C(  3871),
                            INT16_C( 22935), INT16_C(-25734), INT16_C( 17444), INT16_C(  1621),
                            INT16_C(-29331), INT16_C( 25287), INT16_C(-16583), INT16_C( -1156)) },
    { simde_mm256_set_epi16(INT16_C(-11131), INT16_C(-17560), INT16_C( 30989), INT16_C( -1961),
                            INT16_C( 25635), INT16_C(-31167), INT16_C( 13893), INT16_C(-24056),
                            INT16_C( 29937), INT16_C( 24074), INT16_C(  3624), INT16_C( 30721),
                            INT16_C(  7318), INT16_C(-21871), INT16_C(-24159), INT16_C( 27811)),
      simde_mm256_set_epi16(INT16_C(-14801), INT16_C( 18665), INT16_C( 21171), INT16_C(  2083),
                            INT16_C(  9794), INT16_C(-14994), INT16_C( -7071), INT16_C(-14888),
                            INT16_C( 17983), INT16_C(-13129), INT16_C(-28994), INT16_C(  8299),
                            INT16_C( 22982), INT16_C(  2227), INT16_C(-21646), INT16_C(-28910)),
      simde_mm256_set_epi16(INT16_C(  3670), INT16_C( 29311), INT16_C(  9818), INT16_C( -4044),
                            INT16_C( 15841), INT16_C(-16173), INT16_C( 20964), INT16_C( -9168),
                            INT16_C( 11954), INT16_C(-28333), INT16_C( 32618), INT16_C( 22422),
                            INT16_C(-15664), INT16_C(-24098), INT16_C( -2513), INT16_C( -8815)) },
    { simde_mm256_set_epi16(INT16_C(-23995), INT16_C( 25905), INT16_C( -5982), INT16_C( 20058),
                            INT16_C(  2118), INT16_C(  -114), INT16_C(   287), INT16_C(-16504),
                            INT16_C( 12216), INT16_C( 31693), INT16_C(  7692), INT16_C(-10279),
                            INT16_C( -9654), INT16_C( 13919), INT16_C( 14030), INT16_C( -6049)),
      simde_mm256_set_epi16(INT16_C( 18387), INT16_C(  3058), INT16_C( 24810), INT16_C(-31587),
                            INT16_C( 19314), INT16_C(-13527), INT16_C( 20849), INT16_C(-15645),
                            INT16_C(  4064), INT16_C(  5808), INT16_C( 11755), INT16_C( 23823),
                            INT16_C(-12210), INT16_C(  -514), INT16_C(-10077), INT16_C(  8317)),
      simde_mm256_set_epi16(INT16_C( 23154), INT16_C( 22847), INT16_C(-30792), INT16_C(-13891),
                            INT16_C(-17196), INT16_C( 13413), INT16_C(-20562), INT16_C(  -859),
                            INT16_C(  8152), INT16_C( 25885), INT16_C( -4063), INT16_C( 31434),
                            INT16_C(  2556), INT16_C( 14433), INT16_C( 24107), INT16_C(-14366)) },
    { simde_mm256_set_epi16(INT16_C( 16733), INT16_C(-19192), INT16_C(-19177), INT16_C(-13201),
                            INT16_C(-14970), INT16_C(-23573), INT16_C( 23037), INT16_C(-14068),
                            INT16_C( 18230), INT16_C( 11141), INT16_C(  3822), INT16_C(  6182),
                            INT16_C(-23525), INT16_C(-16307), INT16_C( 26522), INT16_C( 21806)),
      simde_mm256_set_epi16(INT16_C(-30186), INT16_C( 24213), INT16_C( 29509), INT16_C(  2127),
                            INT16_C( -4444), INT16_C( 10965), INT16_C(-26578), INT16_C( -9065),
                            INT16_C( -2827), INT16_C( 31843), INT16_C( 28821), INT16_C(  8551),
                            INT16_C( -1781), INT16_C( 16565), INT16_C(-30183), INT16_C(  9876)),
      simde_mm256_set_epi16(INT16_C(-18617), INT16_C( 22131), INT16_C( 16850), INT16_C(-15328),
                            INT16_C(-10526), INT16_C( 30998), INT16_C(-15921), INT16_C( -5003),
                            INT16_C( 21057), INT16_C(-20702), INT16_C(-24999), INT16_C( -2369),
                            INT16_C(-21744), INT16_C( 32664), INT16_C( -8831), INT16_C( 11930)) },
    { simde_mm256_set_epi16(INT16_C(-10649), INT16_C(  1789), INT16_C( 27012), INT16_C(  5765),
                            INT16_C(-10851), INT16_C(  5376), INT16_C( -9175), INT16_C(-28947),
                            INT16_C(  7733), INT16_C(  7167), INT16_C(-27568), INT16_C(  2115),
                            INT16_C( 10120), INT16_C(-30644), INT16_C(-28345), INT16_C( 20915)),
      simde_mm256_set_epi16(INT16_C( 23043), INT16_C( 25420), INT16_C( 19475), INT16_C(-31775),
                            INT16_C(-12265), INT16_C( -4342), INT16_C( 11340), INT16_C( 16492),
                            INT16_C( 28872), INT16_C( -2502), INT16_C(-23877), INT16_C(-30231),
                            INT16_C(  1907), INT16_C(   764), INT16_C(  -427), INT16_C(-25788)),
      simde_mm256_set_epi16(INT16_C( 31844), INT16_C(-23631), INT16_C(  7537), INT16_C(-27996),
                            INT16_C(  1414), INT16_C(  9718), INT16_C(-20515), INT16_C( 20097),
                            INT16_C(-21139), INT16_C(  9669), INT16_C( -3691), INT16_C( 32346),
                            INT16_C(  8213), INT16_C(-31408), INT16_C(-27918), INT16_C(-18833)) },
    { simde_mm256_set_epi16(INT16_C( 10906), INT16_C( -7304), INT16_C(  1755), INT16_C(  4890),
                            INT16_C(-11395), INT16_C( -7564), INT16_C( 10816), INT16_C(-23172),
                            INT16_C(-11608), INT16_C(-11875), INT16_C(-15837), INT16_C(-17763),
                            INT16_C( 21395), INT16_C(  8598), INT16_C(-20063), INT16_C(-10275)),
      simde_mm256_set_epi16(INT16_C( -9448), INT16_C(  6330), INT16_C(-18331), INT16_C( -6901),
                            INT16_C(-14581), INT16_C( 32348), INT16_C(  9963), INT16_C( 31451),
                            INT16_C( 24178), INT16_C( 12481), INT16_C( 12230), INT16_C(-12978),
                            INT16_C(-27030), INT16_C( -1366), INT16_C(-22019), INT16_C( 19232)),
      simde_mm256_set_epi16(INT16_C( 20354), INT16_C(-13634), INT16_C( 20086), INT16_C( 11791),
                            INT16_C(  3186), INT16_C( 25624), INT16_C(   853), INT16_C( 10913),
                            INT16_C( 29750), INT16_C(-24356), INT16_C(-28067), INT16_C( -4785),
                            INT16_C(-17111), INT16_C(  9964), INT16_C(  1956), INT16_C(-29507)) },
    { simde_mm256_set_epi16(INT16_C( 30843), INT16_C( 21336), INT16_C(  5686), INT16_C(  2828),
                            INT16_C( 19954), INT16_C( 31539), INT16_C(-19646), INT16_C(   671),
                            INT16_C( 25132), INT16_C(  3458), INT16_C(-19712), INT16_C(  4606),
                            INT16_C(  5503), INT16_C(-15517), INT16_C(   355), INT16_C( 25145)),
      simde_mm256_set_epi16(INT16_C( -6584), INT16_C( 11532), INT16_C( 13185), INT16_C(-20125),
                            INT16_C( 10954), INT16_C( -8384), INT16_C(  2784), INT16_C( 19614),
                            INT16_C( 16337), INT16_C( 21741), INT16_C( 28414), INT16_C( 19897),
                            INT16_C(-27104), INT16_C( 23081), INT16_C( 17729), INT16_C( 27826)),
      simde_mm256_set_epi16(INT16_C(-28109), INT16_C(  9804), INT16_C( -7499), INT16_C( 22953),
                            INT16_C(  9000), INT16_C(-25613), INT16_C(-22430), INT16_C(-18943),
                            INT16_C(  8795), INT16_C(-18283), INT16_C( 17410), INT16_C(-15291),
                            INT16_C( 32607), INT16_C( 26938), INT16_C(-17374), INT16_C( -2681)) },
    { simde_mm256_set_epi16(INT16_C(-16362), INT16_C(-26163), INT16_C( -8945), INT16_C(  5119),
                            INT16_C( 30284), INT16_C( 12893), INT16_C(-21079), INT16_C(   124),
                            INT16_C( -1271), INT16_C(  3217), INT16_C( 20702), INT16_C(   647),
                            INT16_C(-30215), INT16_C( 25412), INT16_C(   851), INT16_C( 30446)),
      simde_mm256_set_epi16(INT16_C(  8605), INT16_C(-24114), INT16_C( -5979), INT16_C( -9101),
                            INT16_C(  6437), INT16_C(-25374), INT16_C( 24146), INT16_C(-14771),
                            INT16_C(-26765), INT16_C( 30576), INT16_C( 25327), INT16_C(  1225),
                            INT16_C(-13633), INT16_C(-15186), INT16_C(-14472), INT16_C( 31809)),
      simde_mm256_set_epi16(INT16_C(-24967), INT16_C( -2049), INT16_C( -2966), INT16_C( 14220),
                            INT16_C( 23847), INT16_C(-27269), INT16_C( 20311), INT16_C( 14895),
                            INT16_C( 25494), INT16_C(-27359), INT16_C( -4625), INT16_C(  -578),
                            INT16_C(-16582), INT16_C(-24938), INT16_C( 15323), INT16_C( -1363)) },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_sub_epi16(test_vec[i].a, test_vec[i].b);
    simde_assert_m256i_i16(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_sub_epi32(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m256i a;
    simde__m256i b;
    simde__m256i r;
  } test_vec[8] = {
    { simde_mm256_set_epi32(INT32_C(  326943318), INT32_C(-1426446841), INT32_C( -705322739), INT32_C( 1382181134),
                            INT32_C( -752013979), INT32_C( 1926838871), INT32_C(-1267474220), INT32_C(-1807600682)),
      simde_mm256_set_epi32(INT32_C(  251701658), INT32_C( 1304570849), INT32_C(-1313346575), INT32_C(  548342496),
                            INT32_C(  350328631), INT32_C(  492623957), INT32_C(  209048435), INT32_C(  494519967)),
      simde_mm256_set_epi32(INT32_C(   75241660), INT32_C( 1563949606), INT32_C(  608023836), INT32_C(  833838638),
                            INT32_C(-1102342610), INT32_C( 1434214914), INT32_C(-1476522655), INT32_C( 1992846647)) },
    { simde_mm256_set_epi32(INT32_C( -933394757), INT32_C( 2044671684), INT32_C(  359818497), INT32_C( 1070534780),
                            INT32_C( -970998086), INT32_C(-1718071453), INT32_C( 1676992968), INT32_C(-1700643811)),
      simde_mm256_set_epi32(INT32_C( 1601497259), INT32_C( -783324799), INT32_C(  230836562), INT32_C( -793897628),
                            INT32_C( 2109010219), INT32_C( -500991481), INT32_C( 1633364343), INT32_C(-1085575788)),
      simde_mm256_set_epi32(INT32_C( 1760075280), INT32_C(-1466970813), INT32_C(  128981935), INT32_C( 1864432408),
                            INT32_C( 1214958991), INT32_C(-1217079972), INT32_C(   43628625), INT32_C( -615068023)) },
    { simde_mm256_set_epi32(INT32_C(  -51216759), INT32_C( -878749548), INT32_C(-1368701232), INT32_C(-2046658418),
                            INT32_C(-1669301170), INT32_C(-2003910541), INT32_C( 1329758066), INT32_C( 1724000039)),
      simde_mm256_set_epi32(INT32_C(-2019361399), INT32_C( 1441882288), INT32_C(-1015852054), INT32_C(-2140601122),
                            INT32_C( 1393090412), INT32_C(  -54787332), INT32_C(  -18616908), INT32_C(-2129018166)),
      simde_mm256_set_epi32(INT32_C( 1968144640), INT32_C( 1974335460), INT32_C( -352849178), INT32_C(   93942704),
                            INT32_C( 1232575714), INT32_C(-1949123209), INT32_C( 1348374974), INT32_C( -441949091)) },
    { simde_mm256_set_epi32(INT32_C( -198091267), INT32_C( -797938117), INT32_C( 1365606315), INT32_C( 1369771544),
                            INT32_C(  454471573), INT32_C(-1496770990), INT32_C(-1504062345), INT32_C(-1729521659)),
      simde_mm256_set_epi32(INT32_C(-1875378957), INT32_C( 1413357347), INT32_C(-2041380610), INT32_C( 1834864782),
                            INT32_C(  265860555), INT32_C(  367864932), INT32_C(-1203083960), INT32_C(  193499515)),
      simde_mm256_set_epi32(INT32_C( 1677287690), INT32_C( 2083671832), INT32_C( -887980371), INT32_C( -465093238),
                            INT32_C(  188611018), INT32_C(-1864635922), INT32_C( -300978385), INT32_C(-1923021174)) },
    { simde_mm256_set_epi32(INT32_C(-1042833230), INT32_C( 1624054732), INT32_C(  234631196), INT32_C(  738820353),
                            INT32_C(-1501237092), INT32_C(-1737761237), INT32_C(-1663334158), INT32_C( -439342149)),
      simde_mm256_set_epi32(INT32_C(  164170961), INT32_C( 1826341689), INT32_C(-1379584328), INT32_C( -883834236),
                            INT32_C( -145065229), INT32_C( 1276456429), INT32_C(  908937179), INT32_C( 1101978337)),
      simde_mm256_set_epi32(INT32_C(-1207004191), INT32_C( -202286957), INT32_C( 1614215524), INT32_C( 1622654589),
                            INT32_C(-1356171863), INT32_C( 1280749630), INT32_C( 1722695959), INT32_C(-1541320486)) },
    { simde_mm256_set_epi32(INT32_C( 1638607685), INT32_C(-2009128326), INT32_C( -563580109), INT32_C( 1319284819),
                            INT32_C(  -21113241), INT32_C( -656216704), INT32_C(  927278729), INT32_C(  414207795)),
      simde_mm256_set_epi32(INT32_C(-1371308348), INT32_C( 1761271665), INT32_C( 1358250649), INT32_C( -906482895),
                            INT32_C(  540611685), INT32_C(  776022210), INT32_C( 1935373704), INT32_C( -317327387)),
      simde_mm256_set_epi32(INT32_C(-1285051263), INT32_C(  524567305), INT32_C(-1921830758), INT32_C(-2069199582),
                            INT32_C( -561724926), INT32_C(-1432238914), INT32_C(-1008094975), INT32_C(  731535182)) },
    { simde_mm256_set_epi32(INT32_C(-2100986650), INT32_C( 1414058950), INT32_C(-1053542475), INT32_C( -736674814),
                            INT32_C(-2096553410), INT32_C(-1369794669), INT32_C(   26060713), INT32_C(-1294950753)),
      simde_mm256_set_epi32(INT32_C( 2012616977), INT32_C( 1553490078), INT32_C(  324319438), INT32_C(-1664423684),
                            INT32_C( 1284704444), INT32_C( 1334884932), INT32_C(-1343260831), INT32_C( -516360618)),
      simde_mm256_set_epi32(INT32_C(  181363669), INT32_C( -139431128), INT32_C(-1377861913), INT32_C(  927748870),
                            INT32_C(  913709442), INT32_C( 1590287695), INT32_C( 1369321544), INT32_C( -778590135)) },
    { simde_mm256_set_epi32(INT32_C(-1942786341), INT32_C(-1691503678), INT32_C(-1765167726), INT32_C( 1858759286),
                            INT32_C(  627375525), INT32_C(-1868274030), INT32_C(   12505540), INT32_C(  986732702)),
      simde_mm256_set_epi32(INT32_C(-1777720655), INT32_C(-2032047915), INT32_C(  -56259521), INT32_C( -952761137),
                            INT32_C(  805966046), INT32_C(  372017673), INT32_C(   20751226), INT32_C( -331388981)),
      simde_mm256_set_epi32(INT32_C( -165065686), INT32_C(  340544237), INT32_C(-1708908205), INT32_C(-1483446873),
                            INT32_C( -178590521), INT32_C( 2054675593), INT32_C(   -8245686), INT32_C( 1318121683)) },
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_sub_epi32(test_vec[i].a, test_vec[i].b);
    simde_assert_m256i_i32(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm256_xor_si256(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m256i a;
    simde__m256i b;
    simde__m256i r;
  } test_vec[8] = {
    { simde_mm256_set_epi64x(INT64_C( 5259297934522696228), INT64_C( -431388325374833226),
                             INT64_C(-9156654280217339654), INT64_C( 3013799969040676174)),
      simde_mm256_set_epi64x(INT64_C(-5610681863545377343), INT64_C(  612481038911101319),
                             INT64_C( 6883094940018615339), INT64_C( 5567527613349466758)),
      simde_mm256_set_epi64x(INT64_C( -369826194426859547), INT64_C( -973728768696970191),
                             INT64_C(-2348436908296831791), INT64_C( 7246573032282466248)) },
    { simde_mm256_set_epi64x(INT64_C( 3972970387578047990), INT64_C(-3229803026080205617),
                             INT64_C(-6416566799554918012), INT64_C( 7243493956554503841)),
      simde_mm256_set_epi64x(INT64_C(-2328069278528400967), INT64_C( -866344990039815627),
                             INT64_C( 5191362241164177707), INT64_C( 6965508020004735797)),
      simde_mm256_set_epi64x(INT64_C(-1687764814515086257), INT64_C( 2366483896335154938),
                             INT64_C(-1227043938297071441), INT64_C(  300751355152891284)) },
    { simde_mm256_set_epi64x(INT64_C(-2206747055975530789), INT64_C( 4273990306427029435),
                             INT64_C(-8066951550635951807), INT64_C(-6928425273442710875)),
      simde_mm256_set_epi64x(INT64_C(-4939687486626430761), INT64_C(-1679871113178117518),
                             INT64_C( -257233978894060261), INT64_C( 3512456176079583747)),
      simde_mm256_set_epi64x(INT64_C( 6490456006491962892), INT64_C(-3170633551353754167),
                             INT64_C( 7809929228804508762), INT64_C(-5807521855463853914)) },
    { simde_mm256_set_epi64x(INT64_C(-8921324304875098515), INT64_C( 7821700200964206339),
                             INT64_C( 2994261353466796408), INT64_C(-3540068018343188204)),
      simde_mm256_set_epi64x(INT64_C( 4294357400656496399), INT64_C( 3626952931332295508),
                             INT64_C(-7673859083891959013), INT64_C( 1757595472193292730)),
      simde_mm256_set_epi64x(INT64_C(-4636023147992241822), INT64_C( 6834710091372766295),
                             INT64_C(-4896194530503130525), INT64_C(-2973751098574872402)) },
    { simde_mm256_set_epi64x(INT64_C( 6035067220796971838), INT64_C(  776715589999365452),
                             INT64_C( 6384421609504908311), INT64_C(-8816267298986390401)),
      simde_mm256_set_epi64x(INT64_C(-5739247744839421985), INT64_C( 4653816358777581262),
                             INT64_C( 1021833051660996174), INT64_C(-2812490060666099514)),
      simde_mm256_set_epi64x(INT64_C(-2046106215006112543), INT64_C( 5355589079452705666),
                             INT64_C( 6247691286445288025), INT64_C( 6727907985691518137)) },
    { simde_mm256_set_epi64x(INT64_C( 8351942705843556286), INT64_C(-6873744911563016812),
                             INT64_C(-3359807879676804643), INT64_C( 8110291315370526762)),
      simde_mm256_set_epi64x(INT64_C( -126725188666547082), INT64_C( 4977977654704902461),
                             INT64_C(-7727661347289141755), INT64_C( 7453179086506187618)),
      simde_mm256_set_epi64x(INT64_C(-8226449520241153080), INT64_C(-1905346832462535511),
                             INT64_C( 5016522326789730264), INT64_C( 1721087647877354312)) },
    { simde_mm256_set_epi64x(INT64_C(-3541650301143541882), INT64_C( 2340510988864802758),
                             INT64_C(-2484352519219712887), INT64_C(-7823366500674586971)),
      simde_mm256_set_epi64x(INT64_C( 8787496485572343767), INT64_C( 5972980855318355117),
                             INT64_C( 1254817555351506981), INT64_C( 3585972827969393388)),
      simde_mm256_set_epi64x(INT64_C(-5248115586102763439), INT64_C( 8259425971222532971),
                             INT64_C(-3679494355159515988), INT64_C(-6724368097479220151)) },
    { simde_mm256_set_epi64x(INT64_C(-8306510049557921760), INT64_C(-3952727854475033325),
                             INT64_C(-2945542500559658351), INT64_C(  937552523927336948)),
      simde_mm256_set_epi64x(INT64_C( 4952101385331357252), INT64_C( 3142376059888144776),
                             INT64_C(-5526391810306106309), INT64_C( 1965153668529504230)),
      simde_mm256_set_epi64x(INT64_C(-4035158306098612636), INT64_C(-2108000641444326245),
                             INT64_C( 7228588967820590762), INT64_C( 1605387943167658002)) }
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m256i r = simde_mm256_xor_si256(test_vec[i].a, test_vec[i].b);
    simde_assert_m256i_i64(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
  TEST_FUNC(mm256_add_epi8),
  TEST_FUNC(mm256_add_epi16),
  TEST_FUNC(mm256_add_epi32),
  TEST_FUNC(mm256_add_epi64),
  TEST_FUNC(mm256_adds_epu8),

  TEST_FUNC(mm256_and_si256),

  TEST_FUNC(mm256_blendv_epi8),

  TEST_FUNC(mm256_broadcastsi128_si256),

  TEST_FUNC(mm256_cmpgt_epi32),

  TEST_FUNC(mm256_cvtepi8_epi16),
  TEST_FUNC(mm256_cvtepi8_epi32),
  TEST_FUNC(mm256_cvtepi8_epi64),
  TEST_FUNC(mm256_cvtepi16_epi32),
  TEST_FUNC(mm256_cvtepi16_epi64),
  TEST_FUNC(mm256_cvtepi32_epi64),
  TEST_FUNC(mm256_cvtepu8_epi16),
  TEST_FUNC(mm256_cvtepu8_epi32),
  TEST_FUNC(mm256_cvtepu8_epi64),
  TEST_FUNC(mm256_cvtepu16_epi32),
  TEST_FUNC(mm256_cvtepu16_epi64),
  TEST_FUNC(mm256_cvtepu32_epi64),


  TEST_FUNC(mm256_extract_epi8),
  TEST_FUNC(mm256_extract_epi16),
  TEST_FUNC(mm256_extracti128_si256),

  TEST_FUNC(mm256_max_epi16),
  TEST_FUNC(mm256_max_epi32),

  TEST_FUNC(mm256_min_epu8),

  TEST_FUNC(mm256_shuffle_epi8),

  TEST_FUNC(mm256_slli_epi32),

  TEST_FUNC(mm256_sub_epi8),
  TEST_FUNC(mm256_sub_epi16),
  TEST_FUNC(mm256_sub_epi32),

  TEST_FUNC(mm256_srli_epi64),

  TEST_FUNC(mm256_xor_si256),

  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

#if defined(SIMDE_NO_NATIVE)
#  define simde_avx2_test_suite simde_avx2_emul_test_suite
#endif

MunitSuite simde_avx2_test_suite = {
  (char*) "/avx2",
  test_suite_tests,
  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};
