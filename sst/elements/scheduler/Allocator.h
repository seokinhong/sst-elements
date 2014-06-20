// Copyright 2009-2014 Sandia Corporation. Under the terms
// of Contract DE-AC04-94AL85000 with Sandia Corporation, the U.S.
// Government retains certain rights in this software.
// 
// Copyright (c) 2009-2014, Sandia Corporation
// All rights reserved.
// 
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.

#ifndef SST_SCHEDULER_ALLOCATOR_H__
#define SST_SCHEDULER_ALLOCATOR_H__

#include <vector>
#include <string>

#include "Job.h"
#include "Machine.h"

namespace SST {
    namespace Scheduler {

        class AllocInfo;
        class MeshLocation;

        class Allocator {
            public:
                virtual ~Allocator() {}

                virtual std::string getSetupInfo(bool comment) = 0;

                bool canAllocate(Job* j)
                {  
                    return (machine -> getNumFreeProcessors() >= j -> getProcsNeeded());
                }
                bool canAllocate(Job* j, std::vector<MeshLocation*>* available)
                {  
                    return (available -> size() >= (unsigned int)j -> getProcsNeeded());
                }

                //allocates job if possible
                //returns information on the allocation or NULL if it wasn't possible
                //(doesn't make allocation; merely returns info on possible allocation)
                virtual AllocInfo* allocate(Job* job) = 0;

                //in case Allocator wants to know when a job is deallocated
                //added for MBS, which wants to update its data structures
                virtual void deallocate(AllocInfo* aInfo) { }

                //called at end of simulation so allocator can report statistics
                virtual void done() { }

            protected:
                Machine* machine;

        };

    }
}

#endif
