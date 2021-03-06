#ifndef __OSMOSIS_OBJECT_STORE_PURGE_H__
#define __OSMOSIS_OBJECT_STORE_PURGE_H__

#include <unordered_set>
#include <boost/filesystem.hpp>
#include "Osmosis/ObjectStore/Labels.h"
#include "Osmosis/ObjectStore/Store.h"

namespace Osmosis {
namespace ObjectStore
{

class Purge
{
public:
	Purge( Store & store, Labels & labels );

	void purge( boost::filesystem::path & dirToPurge );

private:
	Store &                     _store;
	Labels &                    _labels;
	std::unordered_set< Hash >  _staleHashes;

	void startWithAllObjects( boost::filesystem::path & dirToPurge );

	void takeOutAllLabels();

	void takeOutDirListFile( std::ifstream & dirListFile );

	std::list< std::string > listLabels();

	Purge( const Purge & rhs ) = delete;
	Purge & operator= ( const Purge & rhs ) = delete;
};

} // namespace ObjectStore
} // namespace Osmosis

#endif // __OSMOSIS_OBJECT_STORE_PURGE_H__
