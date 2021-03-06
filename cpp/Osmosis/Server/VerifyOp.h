#ifndef __OSMOSIS_SERVER_VERIFY_OP_H__
#define __OSMOSIS_SERVER_VERIFY_OP_H__

namespace Osmosis {
namespace Server
{

class VerifyOp
{
public:
	VerifyOp( TCPSocket & socket, const ObjectStore::Store & store ) :
		_socket( socket ),
		_store( store )
	{}

	void go()
	{
		BACKTRACE_BEGIN
		Hash hash( _socket.receiveAll< struct Tongue::Hash >() );
		_store.verifyOrDestroy( hash );
		Stream::AckOps( _socket ).sendAck();
		BACKTRACE_END
	}

private:
	TCPSocket & _socket;
	const ObjectStore::Store & _store;

	VerifyOp( const VerifyOp & rhs ) = delete;
	VerifyOp & operator= ( const VerifyOp & rhs ) = delete;
};

} // namespace Server
} // namespace Osmosis

#endif // __OSMOSIS_SERVER_VERIFY_OP_H__
