/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2014 The srsLTE Developers. See the
 * COPYRIGHT file at the top-level directory of this distribution.
 *
 * \section LICENSE
 *
 * This file is part of the srsLTE library.
 *
 * srsLTE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsLTE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * A copy of the GNU Lesser General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

#include <stdint.h>
/******************************************************************************
 *  File:         queue.h
 *
 *  Description:  Queue used at interface of PHY/MAC
 *
 *  Reference:
 *****************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

namespace srslte {
namespace ue {
  
class queue
{
public:

  class element
  {
  public: 
    ~element(); 
    bool release()
    {
      if (state == READY) {
        state = RELEASED; 
        return true; 
      } else {
        return false; 
      }
    }
    bool is_released() 
    {
      return state == RELEASED;
    }
    bool ready_to_send() {
      if (state == RELEASED) {
        state = READY; 
        return true; 
      } else {
        return false; 
      }
    }
    bool is_ready_to_send() {
      return state == READY; 
    }
    uint32_t tti; 
  protected: 
    enum {
     RELEASED, READY
    } state;     
  };
  
  queue(uint32_t nof_elements, uint32_t element_size);
  ~queue();
  
  element* get(uint32_t tti);

private:
  uint32_t nof_elements; 
  uint32_t element_size; 
  element* *buffer_of_elements; 
  
};

}

}
#endif
  