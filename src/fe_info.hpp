/*
 *
 *  Attract-Mode frontend
 *  Copyright (C) 2013 Andrew Mickelson
 *
 *  This file is part of Attract-Mode.
 *
 *  Attract-Mode is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Attract-Mode is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Attract-Mode.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef FE_INFO_HPP
#define FE_INFO_HPP

#include "fe_base.hpp"
#include <map>
#include <vector>
#include <deque>

//
// Class for storing information regarding a specific rom
//
class FeRomInfo : public FeBaseConfigurable
{
public:
	enum Index
	{
		Romname=0,
		Title,
		Emulator,
		Cloneof,
		Year,
		Manufacturer,
		Category,
		Players,
		Rotation,
		Control,
		Status,
		LAST_INDEX
	};
	static const char *indexStrings[];

	FeRomInfo();
	FeRomInfo( const std::string &romname );

	const std::string &get_info( int ) const;
	void set_info( enum Index, const std::string & );

	int process_setting( const std::string &setting, 
								const std::string &value,
								const std::string &fn );
	void dump( void );
	std::string as_output( void ) const;

	bool operator< ( FeRomInfo );

private:
	std::string get_info_escaped( int ) const;

	std::string m_info[LAST_INDEX];
};

//
// Class for storing information regarding a specific Attract-Mode list
//
class FeListInfo : public FeBaseConfigurable
{
public:

	enum Index {
		Name=0,
		Layout,
		Romlist,
		Filter,
		LAST_INDEX
	};

	enum FilterComp {
		FilterEquals=0,
		FilterNotEquals,
		FilterContains,
		FilterNotContains,
		FilterGt,
		FilterLt,
		LAST_COMPARISON
	};

	static const char *indexStrings[];
	static const char *filterCompStrings[];

	FeListInfo( const std::string &name );

	const std::string &get_info( int ) const;
	void set_info( int setting, const std::string &value );

	int process_setting( const std::string &setting, 
								const std::string &value,
								const std::string &fn );

	int process_state( const std::string &state_string );
	std::string state_as_output();

	void dump( void );

	bool get_filter( FeRomInfo::Index &i, FilterComp &c, std::string &w );
	void set_filter( FeRomInfo::Index i, FilterComp c, const std::string &w );

	std::string get_current_layout_file();
	void set_current_layout_file( const std::string & );

	int get_current_rom_index() const;
	void set_current_rom_index( int );

	void save( std::ofstream & );

private:
	int parse_filter( const std::string &fn, const std::string &filter );

	std::string m_info[LAST_INDEX];
	std::string m_current_layout_file;
	int m_rom_index;

	FeRomInfo::Index m_filter_target;
	FilterComp m_filter_comp;
	std::string m_filter_what;
};

class FeRomList : public FeFileConfigurable
{
private:
	FeRomInfo::Index m_filter_target;
	FeListInfo::FilterComp m_filter_comp;
	std::string m_filter_what;

	bool apply_filter( const FeRomInfo &rom );

public:
	std::deque<FeRomInfo> list;

	void set_filter( FeRomInfo::Index i, 
				FeListInfo::FilterComp c, 
				const std::string &w );

	int process_setting( const std::string &setting, 
								const std::string &value,
								const std::string &fn );

	bool empty() const { return list.empty(); };
	int size() const { return (int)list.size(); };
	const FeRomInfo &operator[](int idx) const { return list[idx]; };
	FeRomInfo &operator[](int idx) { return list[idx]; };
};


// 
// Class for storing information regarding a specific emulator
//
class FeEmulatorInfo : public FeFileConfigurable
{
public:

	enum Index
	{
		Name=0,
		Executable,
		Command,
		Rom_path,
		Rom_extension,
		Catver_file, 
		Listxml, 
		Movie_path,
		Movie_artwork,
		LAST_INDEX
	};
	static const char *indexStrings[];
	static const char *indexDispStrings[];

	FeEmulatorInfo();
	FeEmulatorInfo( const std::string &name );

	const std::string &get_info( int ) const;
	void set_info( enum Index, const std::string & );

	bool get_artwork( const std::string &, std::string & );
	void set_artwork( const std::string &, const std::string & );
	void get_artwork_list( std::vector<std::pair<std::string,std::string> > & );
	void delete_artwork( const std::string & );
	
	int process_setting( const std::string &setting, 
								const std::string &value,
								const std::string &filename );
	void dump( void );

	void save( const std::string &filename );

private:
	std::string m_info[LAST_INDEX];
	std::map<std::string, std::string> m_artwork;
};

//
// Class to contain the interface language strings
//
class FeResourceMap : public FeFileConfigurable
{
public:
	FeResourceMap();

	int process_setting( const std::string &setting, 
								const std::string &value,
								const std::string &filename );

	void get_resource( const std::string &token,
				std::string &str );

private:
	std::map<std::string, std::string> m_map;
};

#endif