#pragma once
#include "helper.h"
#include <helper_cuda.h>

class Simulator
{
public:
	Simulator(float gravity, float h, float dt, float pho0, float lambda_eps, uint niter, float3 ulim, float3 llim) 
		: m_gravity(gravity), m_h(h), m_dt(dt), m_pho0(pho0), m_lambda_eps(lambda_eps)
		, m_niter(niter), m_ulim(ulim), m_llim(llim) {
		checkCudaErrors(cudaMalloc(&dc_gridId, sizeof(uint) * MAX_PARTICLE_NUM));
		checkCudaErrors(cudaMalloc(&dc_gridStart, sizeof(uint) * MAX_PARTICLE_NUM));
		checkCudaErrors(cudaMalloc(&dc_gridEnd, sizeof(uint) * MAX_PARTICLE_NUM));
		checkCudaErrors(cudaMalloc(&dc_lambda, sizeof(float) * MAX_PARTICLE_NUM));
		checkCudaErrors(cudaMalloc(&dc_grad, sizeof(float3) * MAX_PARTICLE_NUM));
	};
	~Simulator() {
		checkCudaErrors(cudaFree(dc_gridId));
		checkCudaErrors(cudaFree(dc_gridStart));
		checkCudaErrors(cudaFree(dc_gridEnd));
		checkCudaErrors(cudaFree(dc_lambda));
		checkCudaErrors(cudaFree(dc_grad));
	}

	/* TODO: may swap(d_pos, d_npos), i.e., the destination is assigned by Simulator, rather than caller */
	void step(uint d_pos, uint d_npos, uint d_vel, uint d_nvel, uint d_iid, uint d_niid, int nparticle);
private:
	void advect();
	void buildGridHash();
	void computeGridHashDim();
	void correctDensity();
	void updateVelocity();
	void correctVelocity();

	float3 *dc_pos, *dc_npos, *dc_vel, *dc_nvel;
	uint *dc_iid, *dc_niid;
	uint *dc_gridId, *dc_gridStart, *dc_gridEnd;
	float* dc_lambda;
	float3* dc_grad;

	float m_gravity, m_h, m_dt, m_pho0, m_lambda_eps;
	uint m_niter;
	int m_nparticle;
	float3 m_ulim, m_llim;
	float3 m_real_ulim, m_real_llim;
	uint3 m_gridHashDim;
};
