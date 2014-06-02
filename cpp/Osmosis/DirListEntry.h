#ifndef __OSMOSIS_DIR_LIST_ENTRY_H__
#define __OSMOSIS_DIR_LIST_ENTRY_H__

#include "Osmosis/FileStatus.h"

namespace Osmosis
{

struct DirListEntry
{
	boost::filesystem::path  path;
	FileStatus               status;
	std::unique_ptr< Hash >  hash;

	DirListEntry( const boost::filesystem::path & path, const FileStatus & status ) :
		path( path ),
		status( status )
	{}

	DirListEntry( std::string line )
	{
		boost::trim( line );
		SplitString split( line, '\t' );
		path = boost::trim_copy_if( split.asString(), boost::is_any_of( "\"" ) );
		split.next();
		if ( split.done() )
			THROW( Error, "'" << line << "' is in an invalid format for a dir list entry" );
		FileStatus unserializedStatus( split.asString() );
		status = unserializedStatus;
		split.next();
		if ( split.done() )
			THROW( Error, "'" << line << "' is in an invalid format for a dir list entry" );
		std::string hashString = split.asString();
		if ( hashString != "nohash" )
			hash.reset( new Hash( Hash::fromHex( hashString ) ) );
		split.next();
		if ( not split.done() )
			THROW( Error, "'" << line << "' is in an invalid format for a dir list entry" );
	}

	friend std::ostream & operator<<( std::ostream & os, const DirListEntry & entry )
	{
		os << entry.path << '\t' << entry.status << '\t';
		if ( entry.hash )
			os << * entry.hash;
		else
			os << "nohash";
		os << '\n';
		return os;
	}

private:
	DirListEntry( const DirListEntry & rhs ) = delete;
	DirListEntry & operator= ( const DirListEntry & rhs ) = delete;
};

} // namespace Osmosis

#endif // __OSMOSIS_DIR_LIST_ENTRY_H__