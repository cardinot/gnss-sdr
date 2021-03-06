/*!
 * \file pass_through.cc
 * \brief Implementation of a block that just puts its input in its
 *        output.
 * \author Carlos Aviles, 2010. carlos.avilesr(at)googlemail.com
 *
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2015  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * GNSS-SDR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GNSS-SDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNSS-SDR. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */

#include "pass_through.h"
#include <iostream>
#include <complex>
#include <glog/logging.h>
#include "configuration_interface.h"

using google::LogMessage;

Pass_Through::Pass_Through(ConfigurationInterface* configuration, std::string role,
        unsigned int in_streams,
        unsigned int out_streams) :
        role_(role),
        in_streams_(in_streams),
        out_streams_(out_streams)
{
    std::string default_item_type = "gr_complex";
    item_type_ = configuration->property(role + ".item_type", default_item_type);
    vector_size_ = configuration->property(role + ".vector_size", 1);
    if(item_type_.compare("float") == 0)
        {
            item_size_ = sizeof(float);
        }
    else if(item_type_.compare("gr_complex") == 0)
        {
            item_size_ = sizeof(gr_complex);
        }
    else if(item_type_.compare("short") == 0)
        {
            item_size_ = sizeof(short);
        }
    else if(item_type_.compare("byte") == 0)
        {
            item_size_ = sizeof(char);
        }
    else if(item_type_.compare("cbyte") == 0)
        {
            item_size_ = sizeof(std::complex<unsigned char>);
        }
    else
        {
            LOG(WARNING) << item_type_ << " unrecognized item type. Using float";
            item_size_ = sizeof(float);
        }
    kludge_copy_ = gr::blocks::copy::make(item_size_);
    DLOG(INFO) << "kludge_copy(" << kludge_copy_->unique_id() << ")";
}



Pass_Through::~Pass_Through()
{}



void Pass_Through::connect(gr::top_block_sptr top_block)
{
    DLOG(INFO) << "nothing to connect internally";
}



void Pass_Through::disconnect(gr::top_block_sptr top_block)
{
    // Nothing to disconnect
}



gr::basic_block_sptr Pass_Through::get_left_block()
{
    return kludge_copy_;
}



gr::basic_block_sptr Pass_Through::get_right_block()
{
    return kludge_copy_;
}
