#include <string>
#include <fstream>
#include <cmath>
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/network-module.h"
#include "ns3/packet-sink.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/ipv4-global-routing-helper.h"

using namespace ns3;
NS_LOG_COMPONENT_DEFINE ("TcpBulkSendExample");

// Calculation for mean, standard deviation
float calc_std_dev(float x, float y, float z)
{
  float mean = (x+y+z)/3;
  float sum = pow(x-mean,2) + pow(y-mean, 2) + pow(z-mean, 2);
  float std_dev = sqrt(sum/3);
  return std_dev;
}

void createFile(float throughput[], float afct[]){
  float th_means[9];
  th_means[1] = (throughput[1] + throughput[2] + throughput[3]) / 3;
  th_means[2] = (throughput[4] + throughput[6] + throughput[8]) / 3;
  th_means[3] = (throughput[5] + throughput[7] + throughput[9]) / 3;
  th_means[4] = (throughput[10] + throughput[11] + throughput[12]) / 3;
  th_means[5] = (throughput[13] + throughput[15] + throughput[17]) / 3;
  th_means[6] = (throughput[14] + throughput[16] + throughput[18]) / 3;
  th_means[7] = (throughput[19] + throughput[21] + throughput[23]) / 3;
  th_means[8] = (throughput[20] + throughput[22] + throughput[24]) / 3;

  float th_std[9];
  th_std[1] = calc_std_dev(throughput[1],  throughput[2] , throughput[3]);
  th_std[2] = calc_std_dev(throughput[4] , throughput[6] , throughput[8]);
  th_std[3] = calc_std_dev(throughput[5] , throughput[7] , throughput[9]);
  th_std[4] = calc_std_dev(throughput[10], throughput[11], throughput[12]);
  th_std[5] = calc_std_dev(throughput[13], throughput[15], throughput[17]);
  th_std[6] = calc_std_dev(throughput[14], throughput[16], throughput[18]);
  th_std[7] = calc_std_dev(throughput[19], throughput[21], throughput[23]);
  th_std[8] = calc_std_dev(throughput[20], throughput[22], throughput[24]);

  float afct_means[9];
  afct_means[1] = (afct[1]  + afct[2]  + afct[3]) / 3;
  afct_means[2] = (afct[4]  + afct[6]  + afct[8]) / 3;
  afct_means[3] = (afct[5]  + afct[7]  + afct[9]) / 3;
  afct_means[4] = (afct[10] + afct[11] + afct[12]) / 3;
  afct_means[5] = (afct[13] + afct[15] + afct[17]) / 3;
  afct_means[6] = (afct[14] + afct[16] + afct[18]) / 3;
  afct_means[7] = (afct[19] + afct[21] + afct[23]) / 3;
  afct_means[8] = (afct[20] + afct[22] + afct[24]) / 3;

  float afct_std[9];
  afct_std[1] = calc_std_dev(afct[1] , afct[2] , afct[3]);
  afct_std[2] = calc_std_dev(afct[4] , afct[6] , afct[8]);
  afct_std[3] = calc_std_dev(afct[5] , afct[7] , afct[9]);
  afct_std[4] = calc_std_dev(afct[10], afct[11], afct[12]);
  afct_std[5] = calc_std_dev(afct[13], afct[15], afct[17]);
  afct_std[6] = calc_std_dev(afct[14], afct[16], afct[18]);
  afct_std[7] = calc_std_dev(afct[19], afct[21], afct[23]);
  afct_std[8] = calc_std_dev(afct[20], afct[22], afct[24]);

  std::ofstream outputFile("tcp_ywang284.csv");
  outputFile<<"exp,r1_s1,r2_s1,r3_s1,avg_s1,std_s1,unit_s1,r1_s2,r2_s2,r3_s2,avg_s2,std_s2,unit_s2,";
  outputFile<<"\n";

  outputFile<<"th_1,"<<throughput[1]<<","<<throughput[2]<<","<<throughput[3]<<","<<th_means[1]<<","<<th_std[1]<<","<<"Mbps,"<<",,,,,,\n";
  outputFile<<"th_2,"<<throughput[4]<<","<<throughput[6]<<","<<throughput[8]<<","<<th_means[2]<<","<<th_std[2]<<","<<"Mbps,"<<throughput[5]<<","<<throughput[7]<<","<<throughput[9]<<","<<th_means[3]<<","<<th_std[3]<<",Mbps,\n";
  outputFile<<"th_3,"<<throughput[10]<<","<<throughput[11]<<","<<throughput[12]<<","<<th_means[4]<<","<<th_std[4]<<","<<"Mbps,"<<",,,,,,\n";
  outputFile<<"th_4,"<<throughput[13]<<","<<throughput[15]<<","<<throughput[17]<<","<<th_means[5]<<","<<th_std[5]<<","<<"Mbps,"<<throughput[14]<<","<<throughput[16]<<","<<throughput[18]<<","<<th_means[6]<<","<<th_std[6]<<",Mbps,\n";
  outputFile<<"th_5,"<<throughput[19]<<","<<throughput[21]<<","<<throughput[23]<<","<<th_means[7]<<","<<th_std[7]<<","<<"Mbps,"<<throughput[20]<<","<<throughput[22]<<","<<throughput[24]<<","<<th_means[8]<<","<<th_std[8]<<",Mbps,\n";

  outputFile<<"afct_1,"<<afct[1]<<","<< afct[2]<<","<< afct[3]<<","<< afct_means[1]<<","<<afct_std[1]<<","<<"Seconds,"<<",,,,,,\n";
  outputFile<<"afct_2,"<<afct[4]<<","<< afct[6]<<","<< afct[8]<<","<< afct_means[2]<<","<<afct_std[2]<<","<<"Seconds,"<<afct[5]<<","<<afct[7]<<","<<afct[9]<<","<<afct_means[3]<<","<<afct_std[3]<<",Seconds,\n";
  outputFile<<"afct_3,"<<afct[10]<<","<<afct[11]<<","<<afct[12]<<","<<afct_means[4]<<","<<afct_std[4]<<","<<"Seconds,"<<",,,,,,\n";
  outputFile<<"afct_4,"<<afct[13]<<","<<afct[15]<<","<<afct[17]<<","<<afct_means[5]<<","<<afct_std[5]<<","<<"Seconds,"<<afct[14]<<","<<afct[16]<<","<<afct[18]<<","<<afct_means[6]<<","<<afct_std[6]<<",Seconds,\n";
  outputFile<<"afct_5,"<<afct[19]<<","<<afct[21]<<","<<afct[23]<<","<<afct_means[7]<<","<<afct_std[7]<<","<<"Seconds,"<<afct[20]<<","<<afct[22]<<","<<afct[24]<<","<<afct_means[8]<<","<<afct_std[8]<<",Seconds,\n";
}


int main(int argc, char const *argv[]) {

    NodeContainer node_c;
    node_c.Create(6);
    // node_c: s1, s2, d1, d2, r1, r2
    NodeContainer s1r1 = NodeContainer (node_c.Get (0), node_c.Get (4));
    NodeContainer s2r1 = NodeContainer (node_c.Get (1), node_c.Get (4));
    NodeContainer d1r2 = NodeContainer (node_c.Get (2), node_c.Get (5));
    NodeContainer d2r2 = NodeContainer (node_c.Get (3), node_c.Get (5));
    NodeContainer r1r2 = NodeContainer (node_c.Get (4), node_c.Get (5));

    InternetStackHelper internet;
    internet.Install (node_c);

    PointToPointHelper p2p;
    p2p.SetDeviceAttribute ("DataRate", StringValue ("1Gbps"));

    NetDeviceContainer nd_s1r1 = p2p.Install (s1r1);
    NetDeviceContainer nd_s2r1 = p2p.Install (s2r1);
    NetDeviceContainer nd_r1r2 = p2p.Install (r1r2);
    NetDeviceContainer nd_d1r2 = p2p.Install (d1r2);
    NetDeviceContainer nd_d2r2 = p2p.Install (d2r2);

    // S1 IP
    Ipv4AddressHelper ipv4;
    ipv4.SetBase ("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer i0i4 = ipv4.Assign (nd_s1r1);
    // S2 IP
    ipv4.SetBase ("10.1.2.0", "255.255.255.0");
    Ipv4InterfaceContainer i1i4 = ipv4.Assign (nd_s2r1);
    // R1 to R2 IP
    ipv4.SetBase ("10.1.3.0", "255.255.255.0");
    Ipv4InterfaceContainer i4i5 = ipv4.Assign (nd_r1r2);
    // D1 IP
    ipv4.SetBase ("10.1.4.0", "255.255.255.0");
    Ipv4InterfaceContainer i2i5 = ipv4.Assign (nd_d1r2);
    // D2 IP
    ipv4.SetBase ("10.1.5.0", "255.255.255.0");
    Ipv4InterfaceContainer i3i5 = ipv4.Assign (nd_d2r2);


    Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
    uint16_t port_1 = 80;
    float startTime = 0.0;

std::stringstream nodeId_1, nodeId_2;
nodeId_1 << s1r1.Get(0)->GetId();
nodeId_2 << s2r1.Get(0)->GetId();

std::string sender1 = "/NodeList/" + nodeId_1.str () + "/$ns3::TcpL4Protocol/SocketType";
std::string sender2= "/NodeList/" + nodeId_2.str () + "/$ns3::TcpL4Protocol/SocketType";

int KB = 1024;
// Experiment 1
Config::Set (sender1, TypeIdValue (TypeId::LookupByName ("ns3::TcpBic")));
int count_1 = 0;
while(count_1 <= 2){
   BulkSendHelper S1_source ("ns3::TcpSocketFactory", InetSocketAddress (i2i5.GetAddress (0), port_1));
   S1_source.SetAttribute ("MaxBytes", UintegerValue (50*KB*KB));
   ApplicationContainer S1_App = S1_source.Install (s1r1.Get (0));
   S1_App.Start (Seconds (startTime));
   S1_App.Stop (Seconds (startTime + 20.0));
   PacketSinkHelper D1_sink ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), port_1));
   ApplicationContainer D1_App = D1_sink.Install (d1r2.Get (0));
   D1_App.Start (Seconds (startTime));
   D1_App.Stop (Seconds (startTime + 20.0));
   startTime = startTime + 20.0;
   count_1++;
}

// Experiment 2
Config::Set (sender2, TypeIdValue (TypeId::LookupByName ("ns3::TcpBic")));
int count_2 = 0;
while(count_2 <= 2){
  // S1 send to D1
  BulkSendHelper S1_source ("ns3::TcpSocketFactory", InetSocketAddress (i2i5.GetAddress (0), port_1));
  S1_source.SetAttribute ("MaxBytes", UintegerValue (50*KB*KB));
  ApplicationContainer S1_App = S1_source.Install (s1r1.Get (0));
  S1_App.Start (Seconds (startTime));
  S1_App.Stop (Seconds (startTime + 20.0));
  PacketSinkHelper D1_sink ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), port_1));
  ApplicationContainer D1_App = D1_sink.Install (d1r2.Get (0));
  D1_App.Start (Seconds (startTime));
  D1_App.Stop (Seconds (startTime + 20.0));
  // S2 send to D2
  BulkSendHelper S2_source ("ns3::TcpSocketFactory", InetSocketAddress (i3i5.GetAddress (0), port_1));
  S2_source.SetAttribute ("MaxBytes", UintegerValue (50*KB*KB));
  ApplicationContainer S2_App = S2_source.Install (s2r1.Get (0));
  S2_App.Start (Seconds (startTime));
  S2_App.Stop (Seconds (startTime + 20.0));
  PacketSinkHelper D2_sink ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), port_1));
  ApplicationContainer D2_App = D2_sink.Install (d2r2.Get (0));
  D2_App.Start (Seconds (startTime));
  D2_App.Stop (Seconds (startTime + 20.0));
  startTime = startTime + 20.0;
  count_2++;
}

// Experiment 3
Config::Set (sender1, TypeIdValue (TypeId::LookupByName("ns3::TcpDctcp")));
int count_3 = 0;
while(count_3 <= 2){
   BulkSendHelper S1_source ("ns3::TcpSocketFactory", InetSocketAddress (i2i5.GetAddress (0), port_1));
   S1_source.SetAttribute ("MaxBytes", UintegerValue (50*KB*KB));
   ApplicationContainer S1_App = S1_source.Install (s1r1.Get (0));
   S1_App.Start (Seconds (startTime));
   S1_App.Stop (Seconds (startTime + 20.0));
   PacketSinkHelper D1_sink ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), port_1));
   ApplicationContainer D1_App = D1_sink.Install (d1r2.Get (0));
   D1_App.Start (Seconds (startTime));
   D1_App.Stop (Seconds (startTime + 20.0));
   startTime = startTime + 20.0;
   count_3++;
}

// Experiment 4
Config::Set (sender1, TypeIdValue (TypeId::LookupByName("ns3::TcpDctcp")));
Config::Set (sender2, TypeIdValue (TypeId::LookupByName("ns3::TcpDctcp")));
int count_4 = 0;
while(count_4 <= 2){
  // S1 send to D1
  BulkSendHelper S1_source ("ns3::TcpSocketFactory", InetSocketAddress (i2i5.GetAddress (0), port_1));
  S1_source.SetAttribute ("MaxBytes", UintegerValue (50*KB*KB));
  ApplicationContainer S1_App = S1_source.Install (s1r1.Get (0));
  S1_App.Start (Seconds (startTime));
  S1_App.Stop (Seconds (startTime + 20.0));
  PacketSinkHelper D1_sink ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), port_1));
  ApplicationContainer D1_App = D1_sink.Install (d1r2.Get (0));
  D1_App.Start (Seconds (startTime));
  D1_App.Stop (Seconds (startTime + 20.0));
  // S2 send to D2
  BulkSendHelper S2_source ("ns3::TcpSocketFactory", InetSocketAddress (i3i5.GetAddress (0), port_1));
  S2_source.SetAttribute ("MaxBytes", UintegerValue (50*KB*KB));
  ApplicationContainer S2_App = S2_source.Install (s2r1.Get (0));
  S2_App.Start (Seconds (startTime));
  S2_App.Stop (Seconds (startTime + 20.0));
  PacketSinkHelper D2_sink ("ns3::TcpSocketFactory",InetSocketAddress (Ipv4Address::GetAny (), port_1));
  ApplicationContainer D2_App = D2_sink.Install (d2r2.Get (0));
  D2_App.Start (Seconds (startTime));
  D2_App.Stop (Seconds (startTime + 20.0));
  startTime = startTime + 20.0;
  count_4++;
}

// Experiment 5
Config::Set (sender1, TypeIdValue (TypeId::LookupByName ("ns3::TcpBic")));
Config::Set (sender2, TypeIdValue (TypeId::LookupByName("ns3::TcpDctcp")));
int count_5 = 0;
while(count_5 <= 2){
  // S1 send to D1 using Cubic
  BulkSendHelper S1_source ("ns3::TcpSocketFactory",InetSocketAddress (i2i5.GetAddress (0), port_1));
  S1_source.SetAttribute ("MaxBytes", UintegerValue (50*KB*KB));
  ApplicationContainer S1_App = S1_source.Install (s1r1.Get (0));
  S1_App.Start (Seconds (startTime));
  S1_App.Stop (Seconds (startTime + 20.0));
  PacketSinkHelper D1_sink ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), port_1));
  ApplicationContainer D1_App = D1_sink.Install (d1r2.Get (0));
  D1_App.Start (Seconds (startTime));
  D1_App.Stop (Seconds (startTime + 20.0));
  // S2 send to D2 using Dctcp
  BulkSendHelper S2_source ("ns3::TcpSocketFactory", InetSocketAddress (i3i5.GetAddress (0), port_1));
  S2_source.SetAttribute ("MaxBytes", UintegerValue (50*KB*KB));
  ApplicationContainer S2_App = S2_source.Install (s2r1.Get (0));
  S2_App.Start (Seconds (startTime));
  S2_App.Stop (Seconds (startTime + 20.0));
  PacketSinkHelper D2_sink ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), port_1));
  ApplicationContainer D2_App = D2_sink.Install (d2r2.Get (0));
  D2_App.Start (Seconds (startTime));
  D2_App.Stop (Seconds (startTime + 20.0));
  startTime = startTime + 20.0;
  count_5++;
}


  Ptr<FlowMonitor> flowmon;
  FlowMonitorHelper flowmonHelper;
  flowmon = flowmonHelper.InstallAll();

  p2p.EnablePcapAll("pcap_file", true);
  std::cout<<"start simulation!\n";
  Simulator::Stop (Seconds (startTime));
  Simulator::Run ();
  Simulator::Destroy ();
  flowmon->CheckForLostPackets ();
  Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmonHelper.GetClassifier());
  std::map<FlowId, FlowMonitor::FlowStats> stats = flowmon->GetFlowStats ();
  int idx = 0;
  float throughput[25];
  float afct[25];
  for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i){
    Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);
    if(t.sourceAddress == "10.1.2.1" || t.sourceAddress == "10.1.1.1"){
          ++idx;
          throughput[idx] = i->second.rxBytes * 8.0 / (i->second.timeLastRxPacket.GetSeconds() - i->second.timeFirstTxPacket.GetSeconds())/1024/1024;
          afct[idx] = (i->second.timeLastTxPacket.GetSeconds() - i->second.timeFirstTxPacket.GetSeconds());
      }
  }
  std::cout<<"start creating file.\n";
  createFile(throughput, afct);
  std::cout<<"output file over!\n";
  return 0;
}
