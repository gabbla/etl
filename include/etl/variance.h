///\file

/******************************************************************************
The MIT License(MIT)

Embedded Template Library.
https://github.com/ETLCPP/etl
https://www.etlcpp.com

Copyright(c) 2021 jwellbelove

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#ifndef ETL_VARIANCE_INCLUDED
#define ETL_VARIANCE_INCLUDED

#include "platform.h"
#include "functional.h"
#include "type_traits.h"

#include <math.h>
#include <stdint.h>

namespace etl
{
  namespace private_variance
  {
    //***************************************************************************
    /// Types for generic variance.
    //***************************************************************************
    template <typename TInput, typename TCalc>
    struct variance_traits
    {
      TCalc    sum_of_squares;
      TCalc    sum;
      uint32_t counter;

      //*********************************
      /// Clear the variance.
      //*********************************
      void clear()
      {
        sum_of_squares = TCalc(0);
        sum            = TCalc(0);
        counter        = 0U;
      }
    };

    //***************************************************************************
    /// Types for float variance.
    //***************************************************************************
    template <typename TCalc>
    struct variance_traits<float, TCalc>
    {
      float    sum_of_squares;
      float    sum;
      uint32_t counter;

      //*********************************
      /// Clear the variance.
      //*********************************
      void clear()
      {
        sum_of_squares = float(0);
        sum            = float(0);
        counter        = 0U;
      }
    };

    //***************************************************************************
    /// Types for double variance.
    //***************************************************************************
    template <typename TCalc>
    struct variance_traits<double, TCalc>
    {
      double   sum_of_squares;
      double   sum;
      uint32_t counter;

      //*********************************
      /// Clear the variance.
      //*********************************
      void clear()
      {
        sum_of_squares = double(0);
        sum            = double(0);
        counter        = 0U;
      }
    };
  }

  //***************************************************************************
  /// Variance Type.
  //***************************************************************************
  struct variance_type
  {
    static ETL_CONSTANT bool Sample     = false;
    static ETL_CONSTANT bool Population = true;
  };

  //***************************************************************************
  /// Variance.
  //***************************************************************************
  template <bool Variance_Type, typename TInput, typename TCalc = TInput>
  class variance 
    : public private_variance::variance_traits<TInput, TCalc>
    , public etl::binary_function<TInput, TInput, void>
  {
  private:

    static ETL_CONSTANT int Adjustment = (Variance_Type == variance_type::Population) ? 0 : 1;

  public:

    //*********************************
    /// Constructor.
    //*********************************
    variance()
      : variance_value(0.0)
      , recalculate(true)
    {
      this->clear();
    }

    //*********************************
    /// Constructor.
    //*********************************
    template <typename TIterator>
    variance(TIterator first, TIterator last)
      : variance_value(0.0)
      , recalculate(true)
    {
      this->clear();
      add(first, last);
    }

    //*********************************
    /// Add a pair of values.
    //*********************************
    void add(TInput value)
    {
      this->sum_of_squares += TCalc(value * value);
      this->sum            += TCalc(value);
      ++this->counter;
      recalculate = true;
    }

    //*********************************
    /// Add a range.
    //*********************************
    template <typename TIterator>
    void add(TIterator first, TIterator last)
    {
      while (first != last)
      {
        add(*first++);
      }
    }

    //*********************************
    /// operator ()
    /// Add a pair of values.
    //*********************************
    void operator ()(TInput value)
    {
      add(value);
    }

    //*********************************
    /// operator ()
    /// Add a range.
    //*********************************
    template <typename TIterator>
    void operator ()(TIterator first, TIterator last)
    {
      add(first, last);
    }

    //*********************************
    /// Get the variance.
    //*********************************
    double get_variance()
    {
      if (recalculate)
      {
        variance_value = 0.0;

        if (this->counter != 0)
        {
          double n = double(this->counter);
          double adjustment = 1.0 / (n * (n - Adjustment)) ;

          double square_of_sum = this->sum * this->sum;

          variance_value = (n * this->sum_of_squares - square_of_sum) * adjustment;
        }

        recalculate = false;
      }

      return variance_value;
    }

    //*********************************
    /// Get the variance.
    //*********************************
    operator double()
    {
      return get_variance();
    }

    //*********************************
    /// Get the total number added entries.
    //*********************************
    size_t count() const
    {
      return size_t(this->counter);
    }

  private:
  
    double variance_value;
    bool   recalculate;
  };
}

#endif
