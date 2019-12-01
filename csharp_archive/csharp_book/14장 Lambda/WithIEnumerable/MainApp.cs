using System;
using System.Collections.Generic;
using System.Linq;

namespace WithIEnumerable
{
    class NameCard
    {
        public string Name { get; set; }
        public string Phone { get; set; }
    }

    class MainApp
    {
        static void Main(string[] args)
        {
            List<NameCard> list = new List<NameCard>();

            list.Add(new NameCard() { Name = "박상현", Phone = "010-5162-1234" });
            list.Add(new NameCard() { Name = "이지은", Phone = "010-9712-3361" });
            list.Add(new NameCard() { Name = "정가은", Phone = "010-2133-8871" });
            list.Add(new NameCard() { Name = "김승수", Phone = "010-5512-2003" });

            IEnumerable<NameCard> result = 
                list.Where<NameCard>(namecard => namecard.Name.EndsWith("은"));

            foreach (NameCard namecard in result)
                Console.WriteLine("{0} : {1}", namecard.Name, namecard.Phone);
        }
    }
}
