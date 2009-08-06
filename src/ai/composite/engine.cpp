/* $Id$ */
/*
   Copyright (C) 2009 by Yurii Chernyi <terraninfo@terraninfo.net>
   Part of the Battle for Wesnoth Project http://www.wesnoth.org/

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License version 2
   or at your option any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY.

   See the COPYING file for more details.
*/

/**
 * AI Support engine - creating specific ai components from config
 * @file ai/composite/engine.cpp
 */

#include "engine.hpp"
#include "contexts.hpp"

#include "../../foreach.hpp"
#include "../../log.hpp"

namespace ai {

static lg::log_domain log_ai_composite_engine("ai/composite/engine");
#define DBG_AI_COMPOSITE_ENGINE LOG_STREAM(debug, log_ai_composite_engine)
#define LOG_AI_COMPOSITE_ENGINE LOG_STREAM(info, log_ai_composite_engine)
#define ERR_AI_COMPOSITE_ENGINE LOG_STREAM(err, log_ai_composite_engine)

engine::engine( readonly_context &context, const config &cfg )
	: ai_(context), engine_(cfg["engine"])
{
	LOG_AI_COMPOSITE_ENGINE << "side "<< ai_.get_side() << " : "<<" created engine with name=["<<cfg["name"]<<"]"<<std::endl;
}

engine::~engine()
{
}


void engine::parse_aspect_from_config( readonly_context &context, const config &cfg, const std::string &id, std::back_insert_iterator< std::vector< aspect_ptr > > b )
{
	engine_ptr eng = context.get_engine(cfg);
	if (eng){
		//do not override that method in subclasses which cannot create aspects
		eng->do_parse_aspect_from_config(cfg, id, b);
	}
}

void engine::parse_candidate_action_from_config( rca_context &context, const config &cfg, std::back_insert_iterator<std::vector< candidate_action_ptr > > b )
{
	engine_ptr eng = context.get_engine(cfg);
	if (eng){
		//do not override that method in subclasses which cannot create candidate actions
		eng->do_parse_candidate_action_from_config(context, cfg, b);
	}
}

void engine::parse_engine_from_config( readonly_context &context, const config &cfg, std::back_insert_iterator<std::vector< engine_ptr > > b )
{
	engine_ptr eng = context.get_engine(cfg);
	if (eng){
		//do not override that method in subclasses which cannot create engines
		eng->do_parse_engine_from_config(cfg, b);
	}
}


void engine::parse_goal_from_config( readonly_context &context, const config &cfg, std::back_insert_iterator<std::vector< goal_ptr > > b )
{
	engine_ptr eng = context.get_engine(cfg);
	if (eng){
		//do not override that method in subclasses which cannot create goals
		eng->do_parse_goal_from_config(cfg, b);
	}
}


void engine::parse_stage_from_config( ai_context &context, const config &cfg, std::back_insert_iterator<std::vector< stage_ptr > > b )
{
	engine_ptr eng = context.get_engine(cfg);
	if (eng){
		//do not override that method in subclasses which cannot create stages
		eng->do_parse_stage_from_config(context, cfg, b);
	}
}

void engine::do_parse_aspect_from_config( const config &/*cfg*/, const std::string &/*id*/, std::back_insert_iterator< std::vector<aspect_ptr> > /*b*/ )
{

}


void engine::do_parse_candidate_action_from_config( rca_context &/*context*/, const config &/*cfg*/, std::back_insert_iterator<std::vector< candidate_action_ptr > > /*b*/ ){

}

void engine::do_parse_engine_from_config( const config &/*cfg*/, std::back_insert_iterator<std::vector< engine_ptr > > /*b*/ ){

}


void engine::do_parse_goal_from_config( const config &/*cfg*/, std::back_insert_iterator<std::vector< goal_ptr > > /*b*/ ){

}


void engine::do_parse_stage_from_config( ai_context &/*context*/, const config &/*cfg*/, std::back_insert_iterator<std::vector< stage_ptr > > /*b*/ )
{

}

std::string engine::evaluate(const std::string& /*str*/)
{
	return "evaluate command is not implemented by this engine";
}


std::string engine::get_name() const
{
	return "null";
}


void engine::set_ai_context(ai_context */*context*/)
{
	//do nothing
}

config engine::to_config() const
{
	config cfg;
	cfg["engine"] = engine_;
	cfg["name"] = get_name();
	return cfg;
}

} //end of namespace ai
