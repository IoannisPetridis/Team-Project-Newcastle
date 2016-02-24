#include "PS4Frame.h"
#include <gnmx\basegfxcontext.h>

using namespace sce;

enum FrameState {
	FRAME_READY,
	FRAME_WAITING,
	FRAME_DONE
};

PS4Frame::PS4Frame()
{	
	frameTag = FRAME_READY;

	//Need to allocate memory for our command buffer
	const int bufferBytes = (1 * 1024 * 1024);

	const uint32_t kNumRingEntries = 64;
	const uint32_t cueHeapSize  = Gnmx::ConstantUpdateEngine::computeHeapSize(kNumRingEntries);
	
	//cause of little use of GPU, it is allocated on Garlic, as part of the API to determines when to 
	//renew the constant data 
	void *constantUpdateEngine  = garlicAllocator.allocate(cueHeapSize, Gnm::kAlignmentOfBufferInBytes);
	
	//storing the graphic commands
	void *drawCommandBuffer		= onionAllocator.allocate(bufferBytes , Gnm::kAlignmentOfBufferInBytes);
	
	//GPU data for each frame
	void *constantCommandBuffer = onionAllocator.allocate(bufferBytes , Gnm::kAlignmentOfBufferInBytes);

	//initialize command buffer
	commandBuffer.init(constantUpdateEngine, kNumRingEntries,
		drawCommandBuffer, bufferBytes, constantCommandBuffer, bufferBytes);

	//to register space for special propose
	Gnm::registerResource(nullptr, ownerHandle, drawCommandBuffer	  , bufferBytes,
		"FrameDrawCommandBuffer", Gnm::kResourceTypeDrawCommandBufferBaseAddress, 0);
	Gnm::registerResource(nullptr, ownerHandle, constantUpdateEngine , bufferBytes,
		"FrameConstantUpdateEngine", Gnm::kResourceTypeDrawCommandBufferBaseAddress, 0);
	Gnm::registerResource(nullptr, ownerHandle, constantCommandBuffer, bufferBytes,
		"FrameConstantCommandBuffer", Gnm::kResourceTypeDrawCommandBufferBaseAddress, 0);
}

PS4Frame::~PS4Frame()
{

}

void PS4Frame::StartFrame() {
	BlockUntilReady();
	frameTag = FRAME_WAITING;

	//reset to be ready for filling in 
	commandBuffer.reset();
	commandBuffer.initializeDefaultHardwareState();
}

void PS4Frame::BlockUntilReady() {
	switch (frameTag)
	{
		case FRAME_READY:	return;
		case FRAME_DONE:	return;

		case FRAME_WAITING: {
			int spinCount = 0;
			while (frameTag != FRAME_DONE)
			{
				++spinCount;

				if (frameTag == FRAME_READY) {
					bool a = true;
				}
			}
			frameTag = FRAME_READY;
		}break;

		default:
		break;
	}
}

void  PS4Frame::EndFrame() {
	//write the value FRAME_DONE to frameTag once the frame is done rendering

	commandBuffer.writeImmediateAtEndOfPipeWithInterrupt(Gnm::kEopFlushCbDbCaches, 
		&frameTag, FRAME_DONE, Gnm::kCacheActionNone);
}