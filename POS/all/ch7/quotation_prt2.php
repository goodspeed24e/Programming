<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body  onLoad="window.print()">
<?php 
// -------------���X�Ҧ������渹�ŦX���󪺳�������---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT * FROM  quotationwork  where quwkno=$quwkno";
	$res = mysql_query($SQLStr);
//--------------�p���`���Ƥέ���------------------
	$total=mysql_num_rows($res);
	
?>
<!------ �����C�L,�ǵ��D�ؿ�------>
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="598" border="0" align="center" cellspacing="0" cellpadding="0" >
    <tr > 
      <td width="598"     align="left"><font size="-1"> 
		 <?php
//--------------���ƿ�ܧe�{�γs��---------------
     echo "������<br>";
	 echo "�����渹:".$quwkno."&nbsp;&nbsp;�Ȥ�:".$quwkcust."/".$quwkcustname."&nbsp;&nbsp;�������O:".$quwktype."&nbsp;&nbsp;�������:".$quwksdate."<br>";
?> 
    </font></td>
    </tr>
  </table>
  <table width="602" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td width="602"> 
        <table width="596" border="0" align="center" >
		  <tr> 
            <td  align="left" colspan="4"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>
          <tr>                     
            <td  align="left"><font size="-1">  
             ���~�s��</font>
            </td>
            <td  align="left"><font size="-1">  
              ���~�W��</font>
            </td>
            <td  align="left"><font size="-1">  
              �����ƶq</font>
            </td>
            <td align="left"><font size="-1">  
              ���</font>
            </td>             
          </tr>
		    <tr> 
            <td  align="left" colspan="4"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>		  
	<?php
      //--------------��ܭ��Ƴ������Ƨe�{�γs�������\��-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from quotationwork where quwkno=$quwkno limit $first , 10";
	  $res = mysql_query($SQLStr);
       while (list($quwkno, $quwkprod, $quwkcust, $quwktype, $quwkpric, $quwkqty, $quwksqty, $quwksdate, $quwkunit, $quwkprodname, $quwkcustname)=mysql_fetch_row($res))
		{
        //---------------- ����������ƪ���ƨçe�{----------------
            echo "<tr border='0'>";	
			echo "<td align='left'><font size='-1'>" . $quwkprod  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $quwkprodname . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $quwkqty . "</font></td>\n";	
			echo "<td align='left'><font size='-1'>" . $quwkpric . "</font></td>\n";	
			echo "</tr>";		  	
		}	
?>      
        </table>
      </td>
    </tr>
  </table>    
</form>
</body>
</html>