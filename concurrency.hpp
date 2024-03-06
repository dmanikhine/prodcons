#pragma once
#include <boost/lockfree/spsc_queue.hpp>
#include <boost/atomic.hpp>

#include "mytype.hpp"
#include "readfile.hpp"
#include "transformline.hpp"

inline boost::lockfree::spsc_queue<TVectorLongString, boost::lockfree::capacity<1024>> spsc_queue;
inline boost::atomic_bool done(false);

void producer(TReadFile &readFile);
void consumer(TTransformLine &transformLine);

