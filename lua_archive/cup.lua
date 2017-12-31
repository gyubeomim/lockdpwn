

if (sim_call_type==sim_childscriptcall_initialization) then
    h=simGetObjectHandle("Cup")
    p=simGetObjectPosition(h,-1)
    o=simAddParticleObject(sim_particle_spheres+sim_particle_respondable1to4+sim_particle_particlerespondable,0.011,5000,nil,0,99999,{1,0,0},nil,nil,nil)
    i=0
end


if (sim_call_type==sim_childscriptcall_cleanup) then

end


if (sim_call_type==sim_childscriptcall_actuation) then
    if (i<3) then
        simAddParticleObjectItem(o,{p[1],p[2],p[3]+0.05,p[1],p[2],p[3]+0.05})
        i=i+1
    end
end
